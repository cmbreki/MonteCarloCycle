#ifndef SHAREDMEMORY_H
#define	SHAREDMEMORY_H

#include "Square.h"

typedef struct Memory Memory;

struct Memory{
    int x;         // square's side value
    int in_out;   // the value is 1 if the point is in the cycle and 0 else
    int quit;    // the simulation is finished or not 
};

int AllocateSharedMemory(int n);

Memory * attach_mem( int shmid);

void detach_mem(Memory * addr);

int create_shared_memory();

void write_data(Memory * shmem, int side, int flag);

void read_data(Memory * shmem, Sides * array_sides, int size);

void destroy_mem(int shmid);




#endif	

