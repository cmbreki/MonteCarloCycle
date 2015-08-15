#include "Semaphores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

void init_semaphores(int semid, int number) {

    union semun arg;
    int i;
    arg.val = 0;

    for (i = 0; i < number; i++) {

        if ((semctl(semid, i, SETVAL, arg)) < 0) {
            printf("ERROR in semctl()\n\aSYSTEM: %s\n\n", strerror(errno));
            exit(1);
        }
    }

}

void delete_semaphores(int semid) {

    if ((semctl(semid, 0, IPC_RMID, 0)) < 0) {
        printf("ERROR in semctl()\n\aSYSTEM: %s\n\n", strerror(errno));
    }
}

void up(int semid, int sem) {

    struct sembuf up;

    up.sem_num = sem;
    up.sem_op = 1;
    up.sem_flg = 0;

    if (semop(semid, &up, 1) < 0) {

        printf("ERROR in semop(),up function \n\aSYSTEM: %s\n\n", strerror(errno));
        exit(getpid());
    }
}

void down(int semid, int sem) {
    struct sembuf down;

    down.sem_num = sem;
    down.sem_op = -1;
    down.sem_flg = 0;


    if (semop(semid, &down, 1) < 0) {
        printf("ERROR in semop(),down function \n\aSYSTEM: %s\n\n", strerror(errno));
        exit(getpid());
    }

}
