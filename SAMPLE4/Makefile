# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
	    CPPFLAGS += -O3
		    LDFLAGS += -O3
		else
		    CPPFLAGS += -g
			    LDFLAGS += -g
			endif

all: pathfinder actorconnections

# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o Edge.o Vertex.o

actorconnections: ActorGraph.o Edge.o Vertex.o 

ActorGraph.o: Edge.h Vertex.h

Edge.o: Edge.h

Vertex.o: Vertex.h Edge.h

clean:
		rm -f pathfinder *.o core*


