CC=mpic++
CFLAGS= -fopenmp
all:percolation


percolation:  main.obj NodeBond.obj percolation.obj 
	$(CC)  $(CFLAGS) -obj percolation percolation.obj NodeBond.obj main.obj

main.obj: main.cpp NodeBond.h percolation.h
	$(CC) $(CFLAGS) -cpp  main.cpp percolation.h NodeBond.h
NodeBond.obj: NodeBond.cpp  NodeBond.h percolation.h
	$(CC) $(CFLAGS) -cpp  NodeBond.cpp percolation.h NodeBond.h
percolation.obj: percolation.cpp NodeBond.h percolation.h
	$(CC) $(CFLAGS) -cpp percolation.cpp percolation.h NodeBond.h
