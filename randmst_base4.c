#include <float.h>
#include <math.h>
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
double prims(int v_count, double **adj);
int findMin(int v_count, s_tuple *s_list);
int update_s_list(int v_visited, int s_count, s_tuple *s_list, double **adj);

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
   srandom(time(NULL));
   double *adj[v_count];
   for (int i = 0; i < v_count; i++) {
      adj[i] = (double *)malloc(v_count * sizeof(double));
   }
   graph_type_dim(v_count, atoi(argv[4]), adj);
   printf("{ ");
   for (int i = 0; i < v_count; i ++) {
       printf("{ ");
       for (int j = 0; j < v_count; j ++) {
           printf(" %f, ", adj[i][j]);
       }
       printf(" } %c", '\n');
   }
   printf(" } %c", '\n');

   double sum = prims(v_count, adj);
   printf("SUM IS HERE %f%c", sum, '\n');

   printf("Vertex count: %d%c",  atoi(argv[2]), '\n');
   printf("Trial count: %d%c",  atoi(argv[3]), '\n');
   printf("Dimension count: %d%c", atoi(argv[4]), '\n');
   return 0;

}

/*

    1. Create S [(0, 0), (1, MAX)]...
    2. Create visited {}, and sum = 0
    3. make counter n = v_count
    while (s_count > 0)
    4. add vertex with smallest value to V
    5. add the value to sum
    6. "remove" (vertice, value from S)
        a. can't actually remove, just move last element to element being taken out
        b. subtract one from s_count
    7. s_count--
    8. update S with new vertices
    remove (vertice, value from S)

*/

double prims(int v_count, double **adj) {
    double sum = 0;
    int s_count = v_count;
    printf("%f, %d, %c", sum, s_count, '\n');
    int *visited = (int *)malloc(v_count * sizeof(int));
    s_tuple *s_list = (s_tuple *)malloc(v_count * sizeof(s_tuple));
    // printf("[");
    for (int i = 0; i < v_count; i++) {
        if (i == 0) {
            s_list[i] = (s_tuple) { .v_num = i,
                                    .low_edge = 0 };
        }
        else {
            s_list[i] = (s_tuple) { .v_num = i,
                                    .low_edge = 4 };
        }
        printf("(%d, %f)", s_list[i].v_num, s_list[i].low_edge);
    }
    printf("] %c", '\n');
    while (s_count > 0) {
        int min = findMin(s_count, s_list);

        printf("I found a minimum at index %d which is equal to value %f%c", min, s_list[min].low_edge, '\n');
        sum = sum + s_list[min].low_edge;
        printf("CURRENT SUM: %f%c", sum, '\n');
        int v_visited = s_list[min].v_num;
        printf("VISITED %d%c", v_visited, '\n');
        visited[v_count - s_count] = v_visited;
        printf("LOOK WHAT IS NOW IN VISITED %d%c", visited[v_count - s_count], '\n');
        if (min != s_count - 1) {
            s_list[min] = s_list[s_count - 1];
        }
        s_count = s_count - 1;
        printf("scount is now %d%c", s_count, '\n');
        update_s_list(v_visited, s_count, s_list, adj);
    }

    return sum;
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
    printf("THE LOWEST EDGE HERE IS %f COMING FROM VERTEX %d%c", s_list[index].low_edge, s_list[index].v_num, '\n');
    return index;
}


int update_s_list(int v_visited, int s_count, s_tuple *s_list, double **adj) {
    for (int i = 0; i < s_count; i++) {
        printf("I am comparing table value %f with adjacency value %f%c", s_list[i].low_edge, adj[v_visited][s_list[i].v_num], '\n');
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
                                      .z = 0,
                                      .l = 0  };
            if (dim >= 3) {
                v_array[i].z = (((double)random())/((double)(RAND_MAX)));
            }
            if (dim == 4) {
                v_array[i].l = (((double)random())/((double)(RAND_MAX)));
            }
            printf("x = %f, y = %f, z = %f, l = %f%c", v_array[i].x, v_array[i].y, v_array[i].z, v_array[i].l, '\n');
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
                else if (dim >= 2) {
                    double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z, l_1 = v_array[i].l;
                    double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z, l_2 = v_array[i].l;
                    weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)) + (pow((l_1 - l_2), 2)));
                }
                adj[j][i] = weight;
                adj[i][j] = weight;
                // printf("%f%c", adj[j][i], '\n');
            }
        }
    }
    free(v_array);
    return 0;
}
