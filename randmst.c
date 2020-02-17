#include <stdio.h>
#include <stdlib.h>

 void populateGraph(int type, int v_count, int dimensions, int* v_array, int** adj);


int main(int argc, char** argv) {
   if (argc != 5){
      printf("Usage: ./randmst int numpoints numtrials dimension");
      return 0;
   } else{
      int v_count = atoi(argv[2]);
      //we should probably make a graph object to initialize instead
      int v_array[v_count]; 
      double adj[v_count][v_count];      
      populateGraph(atoi(argv[1]), v_count, atoi(argv[4]), v_array, adj);

      //printing args
      printf("Hello, World!%c", '\n');
      printf("Vertice count: %d%c",  atoi(argv[2]), '\n');
      printf("Trial count: %d%c",  atoi(argv[3]), '\n');
      printf("Dimension count: %d%c", atoi(argv[4]), '\n');
      return 0;
   }
}

//calling one of the three graph types to populate vertices and edges
void populateGraph(int type, int vertices, int dimensions, int vertices[], double adj[][]){
   if (type == 1){
      graph_type_1(v_count, v_array, adj);
   } else if (type == 2){
      graph_type_2(vertices);
   } else {
      graph_type_3(vertices, dimensions);
   }
}



//three types of graphs to implement:

//2D graph, n vertices, each edge has a weight Random [0, 1]
int graph_type_1(int v_count, int v_array[], double adj[][]){
   for (int i = 0; i < v_count; i++){
         v_array[i] = i;
      }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         adj[j][i] = (double)rand();
         adj[i][j] = adj[j][i];
         printf("%d%c", adj[j][i], '\n');
      }
   }

   return 0;
}


//2D graph, n vertices of (x, y) coordinates with random [0, 1], edges are distance between vertices
int graph_type_2(int v_count, Tuple<int,int>v_array[], int adj[][]){
   for (int i = 0; i < v_count; i++){
      v_array[i] = ((double)rand(), (double)rand());
   }
   for (int i = 0; i < v_count; i++){
      for (int j = i; j < v_count; j++){
         (x_1, y_1) = v_array[i];
         (x_2, y_2) = v_array[j];
         double weight = sqrt(pow((x_1 - x_2)) + pow((y_1 - y_2)));
         adj[j][i] = weight;
         adj[i][j] = weight;
      }
   }
   return 0;
}

int graph_type_3(int n, int dimensions){
   //3D/4D graph, n vertices, each vertice x,y,z,?a coordinate Random [0, 1], edges are distance between vertices
   return 0;
}
