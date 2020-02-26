#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct point_4d {
   double x;
   double y;
   double z;
   double l;
} point_4d;

typedef struct s_tuple {
    int v_num;
    double low_edge;
} s_tuple;

typedef struct edge_node {
    int v_num;
    double weight;
    struct edge_node *next;
} edge_node;

int findMin(int v_count, s_tuple *s_list);
int testing(int v_count, int trials, int dimensions, int type);
int update_s_list_point(int v_visited, int s_count, s_tuple *s_list, point_4d *v_array);
double prims_trials (int trials, int dim, int v_count, point_4d *v_array, bool test, edge_node **v0_array);
int graph_no_adj(int v_count, int dim, point_4d *v_array, edge_node **v0_array);
int update_s_list_0(int v_visited, int s_count, s_tuple *s_list, edge_node **v0_array);
double find_weight(int i, int j, edge_node **v0_array);
/*
    TODO:
    1. Make an S function that creates and fills an S array [(0, MAX)...(n-1, MAX)]
    2. Bring Prim function to life
    2.1 Determine what is the max n input for Prim function to work
    3. Averaging method that runs prim >=5 times and averages
    4. 0 method for testing: runs not just n, but different values of n that is less than our max
*/

int main(int argc, char** argv) {

  if (argc != 5) {
    printf("Usage: ./randmst int numpoints numtrials dimension %c", '\n');
    return 1;
  }
  int v_count = atoi(argv[2]);
  if (v_count <= 0) {
     printf("Invalid number of vertices");
     return 1;
  }
  else if (v_count == 1) {
     return 0;
  }
  if (atoi(argv[3]) < 1) {
     printf("Invalid number of trials");
     return 1;
  }
  srandom(time(NULL));

  if (atoi(argv[1]) != 0){
      if (atoi(argv[1]) == 2){
          printf("Time!%c",'\n');
      }
    for (int i = 0; i < 3; i++){
        testing(v_count, atoi(argv[3]), atoi(argv[4]), atoi(argv[1]));

    }
    printf("Vertex count: %d%cDimension count: %d%cMST ", v_count, '\n', atoi(argv[4]), '\n');
    printf("Trial count: %d%c",  atoi(argv[3]), '\n');
    return 0;
  } else {
      double sum_array;

    if (atoi(argv[4]) == 0){
        edge_node **v0_array = (edge_node **)malloc(v_count * sizeof(edge_node));
        for (int i = 0; i < v_count; i++) {
          v0_array[i] = NULL;
        }
        graph_no_adj(v_count, atoi(argv[4]), NULL, v0_array);

        sum_array = prims_trials(atoi(argv[3]), atoi(argv[4]), v_count, NULL, true, v0_array);
        for (int i = 0; i < v_count; i++) {
            edge_node *temp = v0_array[i];
            while (temp) {
                temp = v0_array[i]->next;
                free(v0_array[i]);
                v0_array[i] = temp;
            }
        }
        free(v0_array);
    }
    else {
        point_4d *v_array = (point_4d *)malloc(v_count * sizeof(point_4d));
        graph_no_adj(v_count, atoi(argv[4]), v_array, NULL);
        sum_array = prims_trials(atoi(argv[3]), atoi(argv[4]), v_count, v_array, true, NULL);
        free(v_array);
    }
    printf("Vertex count: %d%cDimension count: %d%cMST total weight: %f%c",
            atoi(argv[2]), '\n', atoi(argv[4]), '\n', sum_array, '\n');

    printf("Trial count: %d%c",  atoi(argv[3]), '\n');



    return 0;
  }
}

int testing(int v_count, int trials, int dimensions, int type){
    double sum_array;
    bool test = (type == 2);

    if (dimensions == 0){
        edge_node **v0_array = (edge_node **)malloc(v_count * sizeof(edge_node));
        graph_no_adj(v_count, dimensions, NULL, v0_array);

        sum_array = prims_trials(1, dimensions, v_count, NULL, test, v0_array);
        free(v0_array);
    }
    else {
        point_4d *v_array = (point_4d *)malloc(v_count * sizeof(point_4d));
        graph_no_adj(v_count, dimensions, v_array, NULL);
        sum_array = prims_trials(1, dimensions, v_count, v_array, test, NULL);
        free(v_array);
    }

    if (type == 1){
         printf("%f%c", sum_array, '\n');
    }


    return 0;
}

/*
    1. Create S [(0, 0), (1, MAX)]...
    2. Create visited {}, and sum = 0
    3. make counter n = v_count
    while (s_count > 0)
    4. add vertex with smallest value to V
    5. add the value to sum
    6. "remove" (vertex, value from S)
        a. can't actually remove, just move last element to element being taken out
        b. subtract one from s_count
    7. s_count--
    8. update S with new vertices
    remove (vertex, value from S)
*/



double prims_trials (int trials, int dim, int v_count, point_4d *v_array, bool test, edge_node **v0_array) {
    clock_t t = clock();
    double avg_sum = 0;
    double max = 0;
    for (int i = 0; i < trials; i ++) {

        double sum = 0;
        int s_count = v_count;
        s_tuple *s_list = (s_tuple *)malloc(v_count * sizeof(s_tuple));
        for (int i = 0; i < v_count; i++) {
            switch (i) {
                case 0:
                    s_list[i] = (s_tuple) { .v_num = i,
                                            .low_edge = 0 };
                    break;
                default:
                    s_list[i] = (s_tuple) { .v_num = i,
                                            .low_edge = 5 };
                    break;
            }
        }
        while (s_count > 0) {
            int min = findMin(s_count, s_list);
            if (max < s_list[min].low_edge) {
                max = s_list[min].low_edge;
            }
            sum += s_list[min].low_edge;
            int v_visited = s_list[min].v_num;
            if (min != s_count - 1) {
                s_list[min] = s_list[s_count - 1];
            }
            s_count--;
            if (dim != 0){
                update_s_list_point(v_visited, s_count, s_list, v_array);
            } else {
                update_s_list_0(v_visited, s_count, s_list, v0_array);
            }


        }
        free(s_list);
        avg_sum += sum;


    }
    t = clock() - t;
        double cpu_time_used = ((double) (t)) / (CLOCKS_PER_SEC * trials);
    if (test){

        printf("time: %f%c", cpu_time_used, '\n');
    }
    printf("max edge weight in MST: %f\n", max);
    return (avg_sum / trials);
}

int findMin(int s_count, s_tuple *s_list) {
    double n = s_list[0].low_edge;
    int index = 0;
    for (int i = 1; i < s_count; i++) {
        if (s_list[i].low_edge < n) {
            n = s_list[i].low_edge;
            index = i;
        }
    }
    return index;
}



int update_s_list_point(int v_visited, int s_count, s_tuple *s_list, point_4d *v_array) {
    double weight, x_i, y_i, z_i, l_i;
    double x_v = v_array[v_visited].x, y_v = v_array[v_visited].y, z_v = v_array[v_visited].z, l_v = v_array[v_visited].l;
    for (int i = 0; i < s_count; i++) {
        x_i = v_array[i].x;
        y_i = v_array[i].y;
        z_i = v_array[i].z;
        l_i = v_array[i].l;
        weight = sqrt((pow((x_v - x_i), 2)) + (pow((y_v - y_i), 2)) + (pow((z_v - z_i), 2)) + (pow((l_v - l_i), 2)));
        if (weight < s_list[i].low_edge) {
            s_list[i].low_edge = weight;
        }
    }

    return 0;
}

double find_weight(int i, int j, edge_node **v0_array) {
  if (!v0_array[i]) {
    return 5;
  }
    edge_node *temp = v0_array[i];
    while (temp) {
        if (temp->v_num == j) {
            return temp->weight;
        }
        temp = temp->next;
    }
    return 5;
}


int update_s_list_0(int v_visited, int s_count, s_tuple *s_list, edge_node **v0_array) {
    double weight;
    for (int i = 0; i < s_count; i++) {
        if (v_visited < i) {
            weight = find_weight(v_visited, i, v0_array);
        }
        else if (i < v_visited) {
            weight = find_weight(i, v_visited, v0_array);
        }
        else {
          continue;
        }
        if (weight < s_list[i].low_edge) {
            s_list[i].low_edge = weight;
        }
    }
    return 0;
}


int graph_no_adj(int v_count, int dim, point_4d *v_array, edge_node **v0_array) {
    double cutoff = 5;
    if (v_count > 140000) {
        cutoff = (3.0/10.0) * (1/(pow(v_count, 2.0/3.0)));
    }
    else if (v_count > 40000) {
        cutoff = (1.0/2.0) * (1/(pow(v_count, 2.0/3.0)));
    }
    else if (v_count > 10000) {
        cutoff = (2.0/3.0) * (1/(pow(v_count, 2.0/3.0)));
    }
    else if (v_count > 1000) {
        cutoff = (1/(pow(v_count, 2.0/3.0)));
    }
    printf("cutoff: %f\n", cutoff);
    for (int i = 0; i < v_count; i++) {
        if (dim != 0) {
            if (v_array){
                v_array[i] = (point_4d) { .x = (((double)random())/((double)(RAND_MAX))),
                                        .y = (((double)random())/((double)(RAND_MAX))),
                                        .z = 0, .l = 0  };

                if (dim >= 3) {
                    v_array[i].z = (((double)random())/((double)(RAND_MAX)));
                }
                if (dim == 4) {
                    v_array[i].l = (((double)random())/((double)(RAND_MAX)));
                }
            }
        } else {
            for (int j = i; j < v_count; j++) {
                if (i == j) {
                  continue;
                }
                edge_node *node = (edge_node *)malloc(sizeof(edge_node));
                node->weight = (((double)random())/((double)(RAND_MAX)));
                if (node->weight > cutoff) {
                    free(node);
                    continue;
                }
                node->v_num = j;
                node->next = v0_array[i];
                v0_array[i] = node;
            }
        }
    }
    return 0;
}
