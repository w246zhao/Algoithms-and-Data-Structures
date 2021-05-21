#List all the drivers
all: kruskaldriver

kruskaldriver: kruskaltest.cpp
	g++ -std=c++11 -o kruskaldriver kruskaltest.cpp graph.cpp disjointSet.cpp

#List all the executables under all
clean:
	rm kruskaldriver