
#include <stdio.h>
#include <stdlib.h>
#include "Square.h"
#include "SharedMemory.h"
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "Semaphores.h" 
#include <sys/ipc.h>
#include <sys/sem.h>


int main(int argc, char * argv[]) {
    
    srand(time(NULL));

    Sides * sides_array;
    int i, k, semid, shmid, status, arraySize, numberOfsems, numberOftests;
    pid_t *proc_ids;
    Memory * shmem;

    k = 0;
    arraySize = argc - 2;
    numberOfsems = argc - 1;
    numberOftests = atoi(argv[argc - 1]);

    
    /*Create the array sides_array*/

    sides_array = (Sides *) malloc((arraySize) * sizeof (Sides));

    if (sides_array == NULL) {
        printf("sides_array is NULL");
        return 0;
    }

     /*Create the array with the processes ids*/
    proc_ids = (pid_t *) malloc((arraySize) * sizeof (pid_t));

    if (proc_ids == NULL) {
        printf("proc_ids is NULL");
        return 0;
    }

    /*Initiate the sides_array*/
    init_sides_array(sides_array, argc, argv);

    /*Initiate the proc_ids array*/
    init_proc_ids(proc_ids, arraySize);


    //create shared memory

    shmid = create_shared_memory();

    shmem = attach_mem(shmid);

   
    // create N+1 semaphores

    semid = semget(IPC_PRIVATE, numberOfsems, 0660 | IPC_CREAT);

    init_semaphores(semid, numberOfsems);

    //creating the n processes
    
    for (i = 0; i < arraySize; i++) {
        proc_ids[i] = fork();
    
            if (proc_ids[i] == 0) { /* In child*/
        
                printf("CHILD: I am the child process %d !\n", i);
                printf("CHILD: Here's my PID: %d\n", getpid());
                printf("CHILD: My parent's PID is: %d\n\n", getppid());

                    while (1) {
                     
                        down(semid, i);
                           if (shmem->quit == 1){ /*If the tests are completed*/
                             break;
                           }
                        shmem->in_out = square(shmem->x); /*read the side from shared memory, */
                        up(semid, numberOfsems - 1); /*call parent process */
                    }
                exit(0); /* exiting after the end of  the tests*/
            }
    }

    /*In parent*/
    printf("PARENT: I am the parent process!\n");
    printf("PARENT: Here's my PID: %d\n\n", getpid());

    
    // Simulation starts
    
    for (i = 0; i < numberOftests; i++) { 
        
        k = (rand() % (argc - 2));   /*generate a random number between 0 and argc-1 */

        //printf("the k in parent  is %d\n\n", k);
        
        write_data(shmem, sides_array[k].side, 0); /*write in shared memory the side*/

        up(semid, k); /*call the process that is going to run the test*/

        down(semid, numberOfsems - 1); /*waiting for the child process to answer*/

        read_data(shmem, sides_array, arraySize); /*read the result from memory and update the sides_array*/
    }
    
    // end of simulation
    
    
    write_data(shmem, 0, 1); /*the tests are completed so update the quit variable in memory*/
    
    for (i = 0; i < arraySize; i++) {    /*Wake all processes and make them exit */
        up(semid, i);  
    }


    while (wait(&status) > 0);
    
    print_proc_ids(proc_ids, arraySize); /*print the array with the processes ids*/
    
    printf("\n---------------------\n");
    
    print_data(sides_array, arraySize); /*print the results*/

    
    
    

    detach_mem(shmem);

    destroy_mem(shmid);

    delete_semaphores(semid);    

    free(sides_array);

    free(proc_ids);

    return 0;

}//end main

