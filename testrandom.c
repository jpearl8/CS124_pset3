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

int main(int argc, char** argv) {
    if (argc != 3){
        printf("add a test #, dim arguments");
        return 1;
    }
    int n = (atoi(argv[1]));
    int dim = (atoi(argv[2]));
    double weight_av = 0;
    point_4d *v_array = (point_4d *)malloc(2 * sizeof(point_4d));
    for (int test = 0; test < n; test++){
        for (int i = 0; i < 2; i++) {
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
        




        double x_1 = v_array[0].x, y_1 = v_array[0].y, z_1 = v_array[0].z, l_1 = v_array[0].l;
        double x_2 = v_array[1].x, y_2 = v_array[1].y, z_2 = v_array[1].z, l_2 = v_array[1].l;
        double weight = sqrt((pow((x_1 - x_2), 2)) + (pow((y_1 - y_2), 2)) + (pow((z_1 - z_2), 2)) + (pow((l_1 - l_2), 2)));
        weight_av += weight;
        printf("%f%c", weight, '\n');
    }
    printf("AVERAGE %f%c", (weight_av/n), '\n');
    return 0;
}