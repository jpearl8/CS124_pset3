#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point {
   double x;
   double y;
   /* declare as many members as desired, but the entire structure size must be known to the compiler. */
} point;

int populateGraph(int type, int v_count, int dimensions, int* v_array,  point* v_array_points, double** adj);
int graph_type_1(int v_count, int* v_array, double** adj);
int graph_type_2(int v_count,  point* v_array, double** adj);



int main(int argc, char** argv) {
   if (argc != 5){
      printf("Usage: ./randmst int numpoints numtrials dimension");
      return 0;
   } else{
      int v_count = atoi(argv[2]);
      //we should probably make a graph object to initialize instead
      int* v_array;
      struct point* v_array_points;
      if (atoi(argv[1]) == 1){
         v_array = (int *)malloc(v_count * sizeof(int)); 
      } else if (atoi(argv[1]) == 2){
         v_array_points = (struct point*)malloc(v_count * sizeof(point));
      }
      double* adj[v_count];
      for (int i = 0; i < v_count; i++){
         adj[i] = (double *)malloc(v_count * sizeof(double)); 
      }
      // double adj[v_count][v_count];      
      populateGraph(atoi(argv[1]), v_count, atoi(argv[4]), v_array, v_array_points, adj);

      //printing args
      printf("Hello, World!%c", '\n');
      printf("Vertice count: %d%c",  atoi(argv[2]), '\n');
      printf("Trial count: %d%c",  atoi(argv[3]), '\n');
      printf("Dimension count: %d%c", atoi(argv[4]), '\n');
      return 0;
   }
}

//calling one of the three graph types to populate vertices and edges
int populateGraph(int type, int v_count, int dimensions, int* v_array, point* v_array_points, double** adj){
   if (type == 1){
      printf("YES%c", '\n');
      graph_type_1(v_count, v_array, adj);
   } else if (type == 2){
      graph_type_2(v_count, v_array_points, adj);
   // } else {
   //    graph_type_3(vertices, dimensions);
   }
   return 0;
}



//three types of graphs to implement:

//2D graph, n vertices, each edge has a weight Random [0, 1]
int graph_type_1(int v_count, int* v_array, double** adj){
   for (int i = 0; i < v_count; i++){
         v_array[i] = i;
      }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         if (i == j){
            adj[j][j] = 0;
         } else {
            double special = (double)rand() / (double)((unsigned)RAND_MAX + 1);
            adj[j][i] = special;
            adj[i][j] = adj[j][i];
            printf("%f%c", adj[j][i], '\n');
         }
      }
   }

   return 0;
}


// //2D graph, n vertices of (x, y) coordinates with random [0, 1], edges are distance between vertices
int graph_type_2(int v_count, point* v_array, double** adj){
   for (int i = 0; i < v_count; i++){
      v_array[i] = (point) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), .y = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
      printf("x = %f, y = %f%c", v_array[i].x, v_array[i].y, '\n');
   }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         if (i == j){
            adj[j][j] = 0;
         } else {
            double x_1 = v_array[i].x, y_1 = v_array[i].y;
            double x_2 = v_array[j].x, y_2 = v_array[j].y;
            double weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)));
            adj[j][i] = weight;
            adj[i][j] = weight;
            printf("%f%c", adj[j][i], '\n');
         }
      }
   }
   return 0;
}

// int graph_type_3(int n, int dimensions){
//    //3D/4D graph, n vertices, each vertice x,y,z,?a coordinate Random [0, 1], edges are distance between vertices
//    return 0;
// }
