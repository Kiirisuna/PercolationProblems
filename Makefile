CC=mpicc
CFLAGS= -fopenmp
DEPS=NodeBond.h percolation.h
OBJ=percolation.o NodeBond.o
%.o: %.cpp $(DEPS)
		$(CC) -cpp -o $@ $< $(CFLAGS)
percolation: $(OBJ)
	mpicc -o $@ $^ $(CFLAGS)