#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "Square.h"


int square(int side) {
    
    double x, y, dist, r;
    double range;
    double div;

    r = (double) side / 2;
   // printf("The r is: %.1f\n",r);
    range = side;
    div = RAND_MAX / range;
    x = (-r) + (rand() / div); /* generate a point (x,y) in the range [-r,+r]  */
    y = (-r) + (rand() / div);

    //printf("The 2 sides are x: %.2f,y:%.2f\n",x,y);

    dist = x * x + y*y;  /*The distance from (0,0)*/

    

    if (dist <= r * r) {
        // printf("In the cicle \n");
        return 1;
    } else {
        //printf(" Out \n");
        return 0;
    }
}

void init_sides_array(Sides * sides_array, int argc, char ** argv) {

    int i;

    for (i = 0; i < argc - 2; i++) {

        sides_array[i].side = atoi(argv[i + 1]);
        //printf("The side is %d\n", sides_array[i].side);
        sides_array[i].tests = 0;
        sides_array[i].in = 0;
    }
}

void init_proc_ids(pid_t * proc_ids, int arraySize) {

    int i;

    for (i = 0; i < arraySize; i++) {

        proc_ids[i] = 0;
    }

}

void print_proc_ids(pid_t * proc_ids, int arraySize) {

    int i;

    for (i = 0; i < arraySize; i++) {

        printf("Process id %d:%d\n", i, proc_ids[i]);

    }
}


void print_data(Sides * sides_array, int size) {
    double f;
    int i;

    for (i = 0; i < size; i++) {
        
        if(sides_array[i].tests==0)
        {
          printf("No tests for side:%d\n\n",sides_array[i].side);
        }
        
        else{ 
          f = (double)(4*sides_array[i].in) / sides_array[i].tests;
          printf("Side:%d \n  Number of tests: %d \n  In circle: %d \n  pi: %f\n", sides_array[i].side, sides_array[i].tests, sides_array[i].in, f);
          printf("-------------------------\n\n");
        }
    }
}



