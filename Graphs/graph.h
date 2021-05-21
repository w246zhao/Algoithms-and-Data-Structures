//
// Created by Wendi Zhao on 2020/11/22.
//

#ifndef ECE250_PROJECT3_GRAPH_H
#define ECE250_PROJECT3_GRAPH_H

#include <exception>

struct illegal_argument : public std::exception
{
    const char * what () const throw ()
    {
        return "invalid argument";
    }
};

class Graph{

private:
    int vertex;
    int edges;
    double **weightMatrix; //use weight to indicate adjacency and weight since weight>0
    int *vertex_degree;

public:
    Graph();
    ~Graph();

    void resize(int m);
    void insert(int u, int v, double w);
    void delete_edge(int u, int v);
    void degree(int u) const;
    void edge_count() const;
    void clear();
    void mst();

};



#endif //ECE250_PROJECT3_GRAPH_H
