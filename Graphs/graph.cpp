//
// Created by Wendi Zhao on 2020/11/22.
//

#include <iostream>
#include <algorithm>
#include "graph.h"
#include "disjointSet.h"
#include <iomanip>

struct edge {
    int u, v;
    double w;
};

bool sortAscending(edge &first_edge, edge &second_edge) {
    return first_edge.w < second_edge.w;
}

Graph::Graph() {
    vertex = 0;
}

Graph::~Graph() {
    if (vertex == 0) {
        return;
    }
    for (int i = 0; i < vertex; i++) {
        delete[] weightMatrix[i];
    }
    delete[] weightMatrix;
    delete[] vertex_degree;
}

void Graph::resize(int m) {
    if (m <= 0) {
        throw illegal_argument();
    }

    if (vertex != 0){
        for (int i = 0; i < vertex; i++) {
            delete[] weightMatrix[i];
        }
        delete[] weightMatrix;
        delete[] vertex_degree;
    }

    vertex = m;
    edges = 0;
    weightMatrix = new double *[m];
    vertex_degree = new int[m];

    for (int i = 0; i < m; i++) {
        weightMatrix[i] = new double[m];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            weightMatrix[i][j] = 0; //0 indicates no edge because weight has to be greater than 0
        }
        vertex_degree[i] = 0;
    }

    std::cout << "success" << std::endl;
}

void Graph::insert(int u, int v, double w) {
    if (u < 0 || v < 0 || w <= 0 || u >= vertex || v >= vertex) {
        throw illegal_argument();
    }
    //updating an edge
    if (weightMatrix[u][v] != 0){
        weightMatrix[u][v] = w;
        weightMatrix[v][u] = w;
        std::cout << "success" << std::endl;
        return;
    }
    //creating a new edge
    weightMatrix[u][v] = w;
    weightMatrix[v][u] = w;
    vertex_degree[u]++;
    vertex_degree[v]++;
    edges++;
    std::cout << "success" << std::endl;
}

void Graph::delete_edge(int u, int v) {
    if (u < 0 || v < 0 || u >= vertex || v >= vertex) {
        throw illegal_argument();
    }

    if (weightMatrix[u][v] == 0) {
        std::cout << "failure" << std::endl;
        return;
    }

    weightMatrix[u][v] = 0;
    weightMatrix[v][u] = 0;
    vertex_degree[v]--;
    vertex_degree[u]--;
    edges--;
    std::cout << "success" << std::endl;
}

void Graph::degree(int u) const {
    if (u < 0 || u >= vertex) {
        throw illegal_argument();
    }

    std::cout << "degree of " << u << " is " << vertex_degree[u] << std::endl;
}

void Graph::edge_count() const {
    std::cout << "edge count is " << edges << std::endl;
}

void Graph::clear() {
    edges = 0;
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            weightMatrix[i][j] = 0;
        }
        vertex_degree[i] = 0;
    }
    std::cout << "success" << std::endl;
}

void Graph::mst() {
    int edgesAdded = 0;
    double totalWeight = 0;
    edge *edge_array;
    edge_array = new edge[edges];
    int count = 0;
    for (int i = 0; i < vertex; i++) {
        for (int j = i; j < vertex; j++) {
            if (weightMatrix[i][j] > 0) {
                edge_array[count].u = i;
                edge_array[count].v = j;
                edge_array[count].w = weightMatrix[i][j];
                count++;
            }
        }
    }

    disjointSet *S = new disjointSet(vertex);

    std::sort(edge_array, edge_array + edges, &sortAscending);


    for (int i = 0; i < edges; i++){
        if (S->findSet(edge_array[i].u) != S->findSet(edge_array[i].v)){
            S->combineSet(edge_array[i].u, edge_array[i].v);
            totalWeight += edge_array[i].w;
            edgesAdded++;
        }
    }

    delete S;
    delete [] edge_array;

    if (edgesAdded < vertex-1){
        std::cout << "not connected" << std::endl;
        return;
    }


    std::cout<<std::fixed;
    std::cout<<std::setprecision(2);
    std::cout<<"mst "<<totalWeight<<std::endl;
}