#ifndef SEMAPHORES_H
#define	SEMAPHORES_H
#include <sys/sem.h>

union semun
{
	int val;
	struct semid_ds *buff;
	unsigned short *array;
};


void init_semaphores(int semid, int number);
void delete_semaphores(int semid);
void up(int semid , int sem);
void down(int semid, int sem);










#endif	/* SEMAPHORES_H */

