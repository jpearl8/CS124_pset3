#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct point_2d {
   double x;
   double y;
} point_2d;

typedef struct point_3d {
   double x;
   double y;
   double z;
} point_3d;

typedef struct point_4d {
   double x;
   double y;
   double z;
   double l;
} point_4d;


int graph_type_0(int v_count, int* v_array, double** adj);
int graph_type_2(int v_count,  point_2d* v_array, double** adj);
int graph_type_3(int v_count, point_3d* v_array, double** adj);
int graph_type_4(int v_count, point_4d* v_array, double** adj);
int graph_type_dim(int v_count, int dim, double** adj);


int main(int argc, char** argv) {
   if (argc != 5){
      printf("Usage: ./randmst int numpoints numtrials dimension");
      return 0;
   } 
   int v_count = atoi(argv[2]);
   //we should probably make a graph object to initialize instead

   double *adj[v_count];
   for (int i = 0; i < v_count; i++){
      adj[i] = (double *)malloc(v_count * sizeof(double)); 
   }

   graph_type_dim(v_count, atoi(argv[4]), adj);
   // if (atoi(argv[4]) == 1){
   //    int* v_array = (int *)malloc(v_count * sizeof(int));
   //    graph_type_0(v_count, v_array, adj);
   // } else if ((atoi(argv[4]) == 2)){
   //    point_2d* v_array = (point_2d*)malloc(v_count * sizeof(point_2d));
   //    graph_type_2(v_count, v_array, adj);
   // } else if ((atoi(argv[4]) == 3)){
   //    point_3d* v_array = (point_3d*)malloc(v_count * sizeof(point_3d));
   //    graph_type_3(v_count, v_array, adj);
   // } else if ((atoi(argv[4]) == 4)){
   //    point_4d* v_array = (point_4d*)malloc(v_count * sizeof(point_4d));
   //    graph_type_4(v_count, v_array, adj);
   // }
   // //condense all graph types other than 0 into 1 function with dimension param
   //make each function free v_array
   //have a function that makes S

   printf("Vertex count: %d%c",  atoi(argv[2]), '\n');
   printf("Trial count: %d%c",  atoi(argv[3]), '\n');
   printf("Dimension count: %d%c", atoi(argv[4]), '\n');
   return 0;
   
}


//three types of graphs to implement:

//2D graph, n vertices, each edge has a weight Random [0, 1]
int graph_type_0(int v_count, int *v_array, double **adj){
   // dont do it
   for (int i = 0; i < v_count; i++){
      v_array[i] = i;
   }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         if (i == j){
            adj[j][j] = 0;
         } else {
            double special = (double)rand() / (double)((unsigned)RAND_MAX + 1);
            // double adj[j][i],  adj[j][i] = (double)rand() / (double)((unsigned)RAND_MAX + 1);
            adj[j][i] = special;
            adj[i][j] = adj[j][i];
            printf("%f%c", adj[j][i], '\n');
         }
      }
   }

   return 0;
}


// //2D graph, n vertices of (x, y) coordinates with random [0, 1], edges are distance between vertices
int graph_type_2(int v_count, point_2d* v_array, double** adj){
   //after v_array, free it and make s
   for (int i = 0; i < v_count; i++){
      v_array[i] = (point_2d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
                              .y = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
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
   // free up v_array

   return 0;
}

//3D graph, n vertices, each vertice x,y,z,?a coordinate Random [0, 1], edges are distance between vertices
int graph_type_3(int v_count, point_3d* v_array, double** adj){
   
   for (int i = 0; i < v_count; i++){
      v_array[i] = (point_3d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
                              .y = (double)rand() / (double)((unsigned)RAND_MAX + 1),
                              .z = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
      printf("x = %f, y = %f, z = %f%c", v_array[i].x, v_array[i].y, v_array[i].z, '\n');
   }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         if (i == j){
            adj[j][j] = 0;
         } else {
            double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z;
            double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z;
            double weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)));
            adj[j][i] = weight;
            adj[i][j] = weight;
            printf("%f%c", adj[j][i], '\n');
         }
      }
   }
   // free v_array
   return 0;
}

//4D graph, n vertices, each vertice x,y,z,?a coordinate Random [0, 1], edges are distance between vertices
int graph_type_4(int v_count, point_4d* v_array, double** adj){
   
   for (int i = 0; i < v_count; i++){
      v_array[i] = (point_4d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
                              .y = (double)rand() / (double)((unsigned)RAND_MAX + 1),
                              .z = (double)rand() / (double)((unsigned)RAND_MAX + 1),
                              .l = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
      printf("x = %f, y = %f, z = %f, l = %f %c", v_array[i].x, v_array[i].y, v_array[i].z, v_array[i].l, '\n');
   }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         if (i == j){
            adj[j][j] = 0;
         } else {
            double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z, l_1 = v_array[i].l;
            double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z, l_2 = v_array[i].l;
            double weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)) + (pow((l_1 - l_2), 2)));
            adj[j][i] = weight;
            adj[i][j] = weight;
            printf("%f%c", adj[j][i], '\n');
         }
      }
   }
   return 0;
}


int graph_type_dim(int v_count, int dim, double** adj){
   switch (dim){
      
      case(4): 
      {
         point_4d *v_array = (point_4d *)malloc(v_count * sizeof(point_4d));
         break;
      }

      case(3):
      {
         point_3d* v_array = (point_3d*)malloc(v_count * sizeof(point_3d));
         break;
      }

      case(2):
      {
         point_2d* v_array = (point_2d*)malloc(v_count * sizeof(point_2d));
         break;
      }
      default:
      {
         int *v_array;
         break;
      }
   }

   for (int i = 0; i < v_count; i++){
      switch(dim){
         case(4):
            v_array[i] = (point_4d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
                              .y = (double)rand() / (double)((unsigned)RAND_MAX + 1),
                              .z = (double)rand() / (double)((unsigned)RAND_MAX + 1),
                              .l = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
            printf("x = %f, y = %f, z = %f, l = %f %c", v_array[i].x, v_array[i].y, v_array[i].z, v_array[i].l, '\n');
            break;
         case(3):
            v_array[i] = (point_3d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
                           .y = (double)rand() / (double)((unsigned)RAND_MAX + 1),
                           .z = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
            printf("x = %f, y = %f, z = %f%c", v_array[i].x, v_array[i].y, v_array[i].z, '\n');
            break;
         case(2):
            v_array[i] = (point_2d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
                           .y = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
            printf("x = %f, y = %f%c", v_array[i].x, v_array[i].y, '\n');
            break;
         default:
            break;
      } 
   }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         if (i == j){
            adj[j][j] = 0;
         } else {
            switch(dim) {
               double weight;
               case(4):
                  double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z, l_1 = v_array[i].l;
                  double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z, l_2 = v_array[i].l;
                  weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)) + (pow((l_1 - l_2), 2)));
                  break;
               case(3):
                  double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z;
                  double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z;
                  weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)));
                  break;
               case(2):
                  double x_1 = v_array[i].x, y_1 = v_array[i].y;
                  double x_2 = v_array[j].x, y_2 = v_array[j].y;
                  weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)));
                  break;
               default:
                  weight = (double)rand() / (double)((unsigned)RAND_MAX + 1);
                  break;
            }
            adj[j][i] = weight;
            adj[i][j] = weight;
            printf("%f%c", adj[j][i], '\n');
         }
      }
   }
   if (dim != 0){
      free(v_array);
   }
   return 0;
}




// int graph_type_dim(int v_count, int dim, double** adj){
//    switch (dim){
      
//       case(4): 
//       {
//          point_4d *v_array = (point_4d *)malloc(v_count * sizeof(point_4d));
//          break;
//       }

//       case(3):
//       {
//          point_3d* v_array = (point_3d*)malloc(v_count * sizeof(point_3d));
//          break;
//       }

//       case(2):
//       {
//          point_2d* v_array = (point_2d*)malloc(v_count * sizeof(point_2d));
//          break;
//       }
//       default:
//       {
//          int *v_array;
//          break;
//    }

//    for (int i = 0; i < v_count; i++){
//       switch(dim){
//          case(4):
//             v_array[i] = (point_4d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
//                               .y = (double)rand() / (double)((unsigned)RAND_MAX + 1),
//                               .z = (double)rand() / (double)((unsigned)RAND_MAX + 1),
//                               .l = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
//             printf("x = %f, y = %f, z = %f, l = %f %c", v_array[i].x, v_array[i].y, v_array[i].z, v_array[i].l, '\n');
//             break;
//          case(3):
//             v_array[i] = (point_3d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
//                            .y = (double)rand() / (double)((unsigned)RAND_MAX + 1),
//                            .z = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
//             printf("x = %f, y = %f, z = %f%c", v_array[i].x, v_array[i].y, v_array[i].z, '\n');
//             break;
//          case(2):
//             v_array[i] = (point_2d) { .x = (double)rand() / (double)((unsigned)RAND_MAX + 1), 
//                            .y = (double)rand() / (double)((unsigned)RAND_MAX + 1) };
//             printf("x = %f, y = %f%c", v_array[i].x, v_array[i].y, '\n');
//             break;
//          default:
//             break;
//       } 
//    }
//    for (int i = 0; i < v_count; i++){
//       for (int j = i; j < v_count; j++){
//          if (i == j){
//             adj[j][j] = 0;
//          } else {
//             switch(dim) {
//                double weight;
//                case(4):
//                   double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z, l_1 = v_array[i].l;
//                   double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z, l_2 = v_array[i].l;
//                   weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)) + (pow((l_1 - l_2), 2)));
//                   break;
//                case(3):
//                   double x_1 = v_array[i].x, y_1 = v_array[i].y, z_1 = v_array[i].z;
//                   double x_2 = v_array[j].x, y_2 = v_array[j].y, z_2 = v_array[j].z;
//                   weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)));
//                   break;
//                case(2):
//                   double x_1 = v_array[i].x, y_1 = v_array[i].y;
//                   double x_2 = v_array[j].x, y_2 = v_array[j].y;
//                   weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)));
//                   break;
//                default:
//                   weight = (double)rand() / (double)((unsigned)RAND_MAX + 1);
//                   break;
//             }
//             adj[j][i] = weight;
//             adj[i][j] = weight;
//             printf("%f%c", adj[j][i], '\n');
//          }
//       }
//    }
//    if (dim != 0){
//       free(v_array);
//    }
//    return 0;
// }