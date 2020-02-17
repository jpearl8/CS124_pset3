#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
   if (argc != 5){
      printf("Usage: ./randmst int numpoints numtrials dimension");
      return 0;
   } else{
      int vertice_count = atoi(argv[2]);
      int vertices[vertice_count]; 
      int adj[vertice_count][vertice_count];
      printf("Hello, World!%c", '\n');
      printf("Vertice count: %d%c",  atoi(argv[2]), '\n');
      printf("Trial count: %d%c",  atoi(argv[3]), '\n');
      printf("Dimension count: %d%c", atoi(argv[4]), '\n');
      return 0;
   }
}

//three types of graphs to implement
int graph_type_1(int n){
   //2D graph, n vertices, each edge has a weight Random [0, 1]
   return 0;
}

int graph_type_2(int n){
   //2D graph, n vertices, each vertice x,y coordinate is random [0, 1], edges are distance between vertices
   return 0;
}

int graph_type_3(int n, int dimensions){
   //3D/4D graph, n vertices, each vertice x,y,z,?a coordinate Random [0, 1], edges are distance between vertices
   return 0;
}
