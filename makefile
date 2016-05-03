FLAGS=-g -O2 -DMONITOR -pg -fast -acc -Minfo 
 
CC=pgcc
#PROGRAM_NAME= genimg
OBJS = main.o readwriteppm.o fitness.o randimage.o compimage.o mate.o mutate.o
 
#$(PROGRAM_NAME): $(OBJS)
#    $(CC) -o $@ $? -lgomp -pg -acc
#
#    #clean:
#    rm  *.o $(PROGRAM_NAME) *~
#
#
#    #makefile for OpenMP
omp:
	pgcc -O2 -mp -g -pg -c -o main.o main.c
	pgcc -O2 -mp -g -pg -c -o readwriteppm.o readwriteppm.c
	pgcc -O2 -mp -g -pg -c -o fitness.o fitness.c
	pgcc -O2 -mp -g -pg -c -o randimage.o randimage.c
	pgcc -O2 -mp -g -pg -c -o compimage.o compimage.c
	pgcc -O2 -mp -g -pg -c -o mate.o mate.c
	pgcc -O2 -mp -g -pg -c -o mutate.o mutate.c
	pgcc -mp -pg -o genimg_omp main.o readwriteppm.o fitness.o randimage.o compimage.o mate.o mutate.o

#OBJS= main.o readwriteppm.o fitness.o randimage.o compimage.o mate.o mutate.o
#omp: $(OBJS)
#    $(CC) -o genimg_omp -fast -DMONITOR -mp -pg -Minfo=accel -lm main.c readwriteppm.c fitness.c randimage.c compimage.c mate.c mutate.c





#make file for OpenACC
#CC=pgcc
#CFLAGS=-fast -acc -Minfo -DMONITOR -ta=tesla,cc35 -O2 -g -pg
#LDFLAGS=-acc -ta=tesla,cc35
#OBJS = main.o readwriteppm.o fitness.o randimage.o compimage.o mate.o mutate.o

acc: 
	pgcc -O2 -acc -Minfo -fast -ta=tesla,cc35 -g -pg -c -o main.o main.c
	pgcc -O2 -acc -Minfo -fast -ta=tesla,cc35 -g -pg -c -o readwriteppm.o readwriteppm.c
	pgcc -O2 -acc -Minfo -fast -ta=tesla,cc35 -g -pg -c -o fitness.o fitness.c
	pgcc -O2 -acc -Minfo -fast -ta=tesla,cc35 -g -pg -c -o randimage.o randimage.c
	pgcc -O2 -acc -Minfo -fast -ta=tesla,cc35 -g -pg -c -o compimage.o compimage.c
	pgcc -O2 -acc -Minfo -fast -ta=tesla,cc35 -g -pg -c -o mate.o mate.c
	pgcc -O2 -acc -Minfo -fast -ta=tesla,cc35 -g -pg -c -o mutate.o mutate.c
	pgcc -acc -pg -Minfo -fast -ta=tesla,cc35 -o genimg_acc main.o readwriteppm.o fitness.o randimage.o compimage.o mate.o mutate.o

#
#    cleanacc:
#        rm *.o acc *~
#
#
#
#
clean:
	rm *.o genimg* *~ 
#
