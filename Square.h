#ifndef SQUARE_H
#define	SQUARE_H

typedef struct Sides Sides;


struct Sides {

    int side;    //square's side value
    int tests;   // the number of test for this side
    int in;      // the number of points in the circle

};


int square(int side);
void init_sides_array(Sides * sides_array , int argc , char ** argv);
void print_data(Sides * sides_array, int size);
void init_proc_ids(pid_t * proc_ids ,int arraySize);
void print_proc_ids(pid_t * proc_ids , int arraySize);




#endif	/* SQUARE_H */

