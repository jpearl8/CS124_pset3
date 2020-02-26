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

int graph_type_dim(int v_count, int dim, double** adj);
int findMin(int v_count, s_tuple *s_list);
int update_s_list(int v_visited, int s_count, s_tuple *s_list, double **adj);
double prims_trials(int trials, int v_count, double **adj, bool time);
int testing(int v_count, int trials, int dimensions, int type);

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
    for (int i = 0; i < 3; i++){
        testing(v_count, atoi(argv[3]), atoi(argv[4]), atoi(argv[1]));

    }
    printf("Vertex count: %d%cDimension count: %d%cMST ", v_count, '\n', atoi(argv[4]), '\n');
    printf("Trial count: %d%c",  atoi(argv[3]), '\n');
    return 0;
  } else {

    double *adj[v_count];
    for (int i = 0; i < v_count; i++) {
        adj[i] = (double *)malloc(v_count * sizeof(double));
    }
    graph_type_dim(v_count, atoi(argv[4]), adj);
    double sum_array = prims_trials(atoi(argv[3]), v_count, adj, true);
    for (int i = 0; i < v_count; i++) {
        free(adj[i]);
    }

    printf("Vertex count: %d%cDimension count: %d%cMST total: %f%c",
            atoi(argv[2]), '\n', atoi(argv[4]), '\n', sum_array, '\n');

    printf("Trial count: %d%c",  atoi(argv[3]), '\n');



    return 0;
  }
}

int testing(int v_count, int trials, int dimensions, int type){
    double *adj[v_count];
    for (int i = 0; i < v_count; i++) {
        adj[i] = (double *)malloc(v_count * sizeof(double));
    }
    graph_type_dim(v_count, dimensions, adj);
    bool test = (type == 2);
    double sum_array = prims_trials(trials, v_count, adj, test);
    for (int i = 0; i < v_count; i++) {
        free(adj[i]);
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

double prims_trials(int trials, int v_count, double **adj, bool test) {
    clock_t t = clock();
    double avg_sum = 0;
    double max;
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
            max = 0;
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
            update_s_list(v_visited, s_count, s_list, adj);

        }
        free(s_list);
        avg_sum += sum;


    }
    t = clock() - t;
        double cpu_time_used = ((double) (t)) / (CLOCKS_PER_SEC * trials);
    if (test){
        // printf("Time: %f seconds%c", cpu_time_used, '\n');
        printf("%f%c", cpu_time_used, '\n');
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

int update_s_list(int v_visited, int s_count, s_tuple *s_list, double **adj) {
    for (int i = 0; i < s_count; i++) {
        if (adj[v_visited][s_list[i].v_num] < s_list[i].low_edge) {
            s_list[i].low_edge = adj[v_visited][s_list[i].v_num];
        }
    }
    return 0;
}

int graph_type_dim(int v_count, int dim, double **adj) {
    point_4d *v_array = (point_4d *)malloc(v_count * sizeof(point_4d));
    for (int i = 0; i < v_count; i++) {
        if (dim != 0) {
            v_array[i] = (point_4d) { .x = (((double)random())/((double)(RAND_MAX))),
                                      .y = (((double)random())/((double)(RAND_MAX))),
                                      .z = 0, .l = 0  };

            // (double)rand() / (double)((unsigned)RAND_MAX + 1)
            if (dim >= 3) {
                v_array[i].z = (((double)random())/((double)(RAND_MAX)));
            }
            if (dim == 4) {
                v_array[i].l = (((double)random())/((double)(RAND_MAX)));
            }
        }
    }

    for (int i = 0; i < v_count; i++) {
        for (int j = i; j < v_count; j++) {
            if (i == j) {
                adj[j][j] = 0;
            } else {
                double weight;
                if (dim == 0) {
                    weight = (((double)random())/((double)(RAND_MAX)));
                }
                else {
                    double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z, l_1 = v_array[i].l;
                    double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z, l_2 = v_array[i].l;
                    weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)) + (pow((l_1 - l_2), 2)));
                }
                adj[j][i] = weight;
                adj[i][j] = weight;
            }
        }
    }
    free(v_array);
    return 0;
}
