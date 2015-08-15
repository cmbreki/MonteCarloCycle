#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include "SharedMemory.h"
#include "Square.h"

int AllocateSharedMemory(int memory_size) {
    int shmid;

      if ((shmid = shmget(IPC_PRIVATE, memory_size, 0660 | IPC_CREAT)) < 0) {
         printf("ERROR in shmget()\n\aSYSTEM: %s\n\n", strerror(errno));
         exit(1);
      }

    return shmid;
}

Memory * attach_mem(int shmid) {

    Memory * shmem;

       if ((shmem = (Memory*) shmat(shmid, NULL, 0)) == (Memory *) - 1) {
          printf("ERROR in shmat()\n\aSYSTEM: %s\n\n", strerror(errno));
          exit(1);
       }

    return shmem;
}

void detach_mem(Memory * memory) {

    if (shmdt((void*) memory) < 0) {
        printf("ERROR in shmdt()\n\aSYSTEM: %s\n\n", strerror(errno));

    }
}

int create_shared_memory() {
    int id;
    
    id = AllocateSharedMemory(sizeof (Memory));

    return id;

}

void destroy_mem(int shmid) {

    if (shmctl(shmid, 0, IPC_RMID) < 0) {
        printf("ERROR in shmctl()\n\aSYSTEM: %s\n\n", strerror(errno));
    }

}

void read_data(Memory * shmem, Sides * array_sides, int size) {
    int i;

    for (i = 0; i < size; i++) {
        if (shmem->x == array_sides[i].side) {
            array_sides[i].tests++;


            if (shmem->in_out == 1) {
                array_sides[i].in++;
            }
            break;
        }
    }

}

void write_data(Memory * shmem, int side, int quit) {

    shmem->x = side;
    shmem->in_out = 0;
    shmem->quit = quit;
}



