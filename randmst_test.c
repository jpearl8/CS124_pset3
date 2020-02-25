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

int graph_no_adj(int v_count, int dim, point_4d *v_array);
int findMin(int v_count, s_tuple *s_list);
int update_s_list_lack0(int v_visited, int s_count, s_tuple *s_list, long time_to_code);
// int testing(int v_count, int trials, int dimensions, int type);
int update_s_list_lack(int v_visited, int s_count, s_tuple *s_list, point_4d *v_array);
double prims_trials_lack (int trials, int dim, int v_count, point_4d *v_array, bool test, long time_to_code);

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
  long time_to_code = time(NULL);

  if (atoi(argv[1]) != 0){
    for (int i = 0; i < 3; i++){
        // testing(v_count, atoi(argv[3]), atoi(argv[4]), atoi(argv[1]));

    }
    printf("Vertex count: %d%cDimension count: %d%cMST ", v_count, '\n', atoi(argv[4]), '\n');
    printf("Trial count: %d%c",  atoi(argv[3]), '\n');
    return 0;
  } else {
      double sum_array;
    // if (atoi(argv[4]) != 0){
    if (atoi(argv[4]) == 0){
        sum_array = prims_trials_lack(atoi(argv[3]), atoi(argv[4]), v_count, NULL, true, time_to_code);
    }
    else {
        point_4d *v_array = (point_4d *)malloc(v_count * sizeof(point_4d));
        graph_no_adj(v_count, atoi(argv[4]), v_array);
        sum_array = prims_trials_lack(atoi(argv[3]), atoi(argv[4]), v_count, v_array, true, time_to_code);
        free(v_array);
    }

    // } else {
    //     double *adj[v_count];
    //     for (int i = 0; i < v_count; i++) {
    //         adj[i] = (double *)malloc(v_count * sizeof(double));
    //     }
    //     graph_type_dim(v_count, atoi(argv[4]), adj);
    //     sum_array = prims_trials(atoi(argv[3]), v_count, adj, true);
    //     for (int i = 0; i < v_count; i++) {
    //         free(adj[i]);
    //     }
    // }
    printf("Vertex count: %d%cDimension count: %d%cMST total: %f%c",
            atoi(argv[2]), '\n', atoi(argv[4]), '\n', sum_array, '\n');

    printf("Trial count: %d%c",  atoi(argv[3]), '\n');



    return 0;
  }
}

// int testing(int v_count, int trials, int dimensions, int type){
//     double *adj[v_count];
//     for (int i = 0; i < v_count; i++) {
//         adj[i] = (double *)malloc(v_count * sizeof(double));
//     }
//     graph_type_dim(v_count, dimensions, adj);
//     bool test = (type == 2);
//     double sum_array = prims_trials(trials, v_count, adj, test);
//     for (int i = 0; i < v_count; i++) {
//         free(adj[i]);
//     }
//     if (type == 1){
//          printf("%f%c", sum_array, '\n');
//     }


//     return 0;
// }

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



double prims_trials_lack (int trials, int dim, int v_count, point_4d *v_array, bool test, long time_to_code) {
    clock_t t = clock();
    double avg_sum = 0;
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
            sum += s_list[min].low_edge;
            int v_visited = s_list[min].v_num;
            if (min != s_count - 1) {
                s_list[min] = s_list[s_count - 1];
            }
            s_count--;
            if (dim != 0){
                update_s_list_lack(v_visited, s_count, s_list, v_array);
            } else {
                update_s_list_lack0(v_visited, s_count, s_list, time_to_code);
            // update_s_list(v_visited, s_count, s_list, adj);
            }


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



int update_s_list_lack(int v_visited, int s_count, s_tuple *s_list, point_4d *v_array) {
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


int update_s_list_lack0(int v_visited, int s_count, s_tuple *s_list, long time_to_code) {
    double weight;
    for (int i = 0; i < s_count; i++) {
        // srandom(i * v_visited * time_to_code);
        weight = (((double)random())/((double)(RAND_MAX)));
        if (weight < s_list[i].low_edge) {
            s_list[i].low_edge = weight;
        }
    }
    return 0;
}





int graph_no_adj(int v_count, int dim, point_4d *v_array) {
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
        }
    }
    return 0;
}