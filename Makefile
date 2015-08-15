#
# In order to execute this "Makefile" just type "make"
#
#

OBJS 	= main.o Semaphores.o SharedMemory.o Square.o
SOURCE	= main.c Semaphores.c SharedMemory.c Square.c 
HEADER  = Semaphores.h SharedMemory.h Square.h
OUT  	= pi
CC	= gcc
FLAGS   = -g -c -lm
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lm

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c

Semaphores.o: Semaphores.c
	$(CC) $(FLAGS) Semaphores.c

SharedMemory.o: SharedMemory.c
	$(CC) $(FLAGS) SharedMemory.c

Square.o: Square.c
	$(CC) $(FLAGS) Square.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)
