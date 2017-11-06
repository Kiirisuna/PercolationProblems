CC=mpicc
CFLAGS= -fopenmp
DEPS=NodeBond.h percolation.h
OBJ=percolation.o NodeBond.o main.o

percolation: percolation.o NodeBond.o main.o
	$(CC)  $(CFLAGS) -o percolation percolation.o NodeBond.o main.o

main.o: main.cpp $(DEPS)
	$(CC) $(CFLAGS) -cpp main.cpp
NodeBond.o: NodeBond.cpp $(DEPS)
	$(CC) $(CFLAGS) -cpp NodeBond.cpp
percolation.o: percolation.cpp $(DEPS)
	$(CC) $(CFLAGS) -cpp percolation.cpp
percolation: percolation.o NodeBond.o main.o
	$(CC)  $(CFLAGS) -o percolation percolation.o NodeBond.o main.o
