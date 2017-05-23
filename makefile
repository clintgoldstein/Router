# Make file for maze solver assignment.

OBJS	= main.o routerSim.o
OBJS1	= bTreeTest.o
CC	= g++
DEPS	= routerSim.h bTree.h linkedQueue.h

all: main bTreeTest

main: main.o routerSim.o $(DEPS)
	$(CC) -g -Wall -pedantic -o main $(OBJS)

main.o: main.cpp $(DEPS)
	$(CC) -g -Wall -pedantic -c main.cpp

routerSim.o: routerSim.cpp $(DEPS)
	$(CC) -g -Wall -pedantic -c routerSim.cpp


bTreeTest: bTreeTest.o $(DEPS)
	$(CC) -g -Wall -pedantic -o bTreeTest $(OBJS1)

bTreeTest.o: bTreeTest.cpp $(DEPS)
	$(CC) -g -Wall -pedantic -c bTreeTest.cpp


# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

