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

int find_min(int v_count, s_tuple *s_list);
double find_weight(int i, int j, edge_node **v0_array);
int graph(int v_count, int dim, point_4d *v_array, edge_node **v0_array);
double prims(int trials, int dim, int v_count, point_4d *v_array, edge_node **v0_array);
int update_s_list_point(int v_visited, int s_count, s_tuple *s_list, point_4d *v_array);
int update_s_list_0(int v_visited, int s_count, s_tuple *s_list, edge_node **v0_array);

int main(int argc, char** argv) {

  // Ensure correct usage
  if (argc != 5) {
    printf("Usage: ./randmst 0 numpoints numtrials dimension \n");
    return 1;
  }
  int v_count = atoi(argv[2]);
  if (v_count <= 0) {
     printf("Invalid number of vertices\n");
     return 1;
  }
  else if (v_count == 1) {
     return 0;
  }
  if (atoi(argv[3]) < 1) {
     printf("Invalid number of trials\n");
     return 1;
  }
  if (atoi(argv[4]) == 1) {
     printf("Invalid number of dimensions\n");
     return 1;
  }

  // Seed RNG with current time
  srandom(time(NULL));

  double sum_array;

  // Dimension 0 requires storing edge weight information
  if (atoi(argv[4]) == 0){
      // Initialize an array of linked lists
      edge_node **v0_array = (edge_node **)malloc(v_count * sizeof(edge_node));
      for (int i = 0; i < v_count; i++) {
        v0_array[i] = NULL;
      }
      // Construct the graph
      graph(v_count, atoi(argv[4]), NULL, v0_array);

      // Extract the weight of the MST using Prim's and free the edge weight array
      sum_array = prims(atoi(argv[3]), atoi(argv[4]), v_count, NULL, v0_array);
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
  // For dimensions 2, 3, and 4, we only need to store the points
  else {
      // Construct the graph and extract the weight of the MST using Prim's, free the array
      point_4d *v_array = (point_4d *)malloc(v_count * sizeof(point_4d));
      graph(v_count, atoi(argv[4]), v_array, NULL);
      sum_array = prims(atoi(argv[3]), atoi(argv[4]), v_count, v_array, NULL);
      free(v_array);
  }

  printf("MST total weight: %f\n\nNumber of vertices: %d\nNumber of dimensions: %d\n",
          sum_array, atoi(argv[2]), atoi(argv[4]));
  printf("Number of trials: %d\n",  atoi(argv[3]));

  return 0;

}

// Implement Prim's algorithm, allowing for multiple trials
double prims(int trials, int dim, int v_count, point_4d *v_array, edge_node **v0_array) {
    // Time the execution of this function
    clock_t t = clock();

    double avg_sum = 0;

    // Execute and average the result of multiple trials (as input by the user)
    for (int i = 0; i < trials; i ++) {
        double sum = 0;
        int s_count = v_count;
        s_tuple *s_list = (s_tuple *)malloc(v_count * sizeof(s_tuple));

        // Construct list of vertices and their lowest edge weight
        for (int i = 0; i < v_count; i++) {
            switch (i) {
                // By default, we pick the first vertex in our graph
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

        // Prim's
        while (s_count > 0) {
            int min = find_min(s_count, s_list);
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
    printf("Runtime in seconds: %f\n", cpu_time_used);

    return (avg_sum / trials);
}

// Find the vertex with the minimum edge
int find_min(int s_count, s_tuple *s_list) {
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

// For dimensions 2, 3, and 4, update minimum weight of edges as needed
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

// For dimension 0, find the weight of edge (i, j) by searching the array of linked lists
double find_weight(int i, int j, edge_node **v0_array) {
    if (!v0_array[i]) {
      // Return 5 if edge is not found
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

// For dimension 0, update minimum weight of edges as needed
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

// Construct the random graph
int graph(int v_count, int dim, point_4d *v_array, edge_node **v0_array) {
    // For dimension 0, we use a cutoff value to "throw" away edges that likely won't
    // form part of the final MST. This optimizes for space.
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

    // We want v_count number of vertices
    for (int i = 0; i < v_count; i++) {
        // For dimensions 2, 3, and 4, it suffices to generate the random points only
        if (dim != 0) {
            if (v_array) {
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
        // For dimension 0, we store edge weights only
        else {
            for (int j = i; j < v_count; j++) {
                // Don't waste space on edges from i to i
                if (i == j) {
                  continue;
                }
                edge_node *node = (edge_node *)malloc(sizeof(edge_node));
                node->weight = (((double)random())/((double)(RAND_MAX)));

                // Don't store edges whose weight is above the cutoff value
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
