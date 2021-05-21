//
// Created by Wendi Zhao on 2020/11/22.
//

#ifndef ECE250_PROJECT3_DISJOINTSET_H
#define ECE250_PROJECT3_DISJOINTSET_H

struct LinkedList;
struct node;

struct LinkedList{
    node *headptr = nullptr;
    node *tailptr = nullptr;
    int length = 0;
};

struct node{
    int value;
    node* next = nullptr;
    LinkedList* representative = nullptr;
};

class disjointSet {
private:
    LinkedList * set;
    int totalSets;
public:
    disjointSet(int sets);
    ~disjointSet();
    void makeSet(int x);
    int findSet(int n);
    void combineSet (int x, int y);
};


#endif //ECE250_PROJECT3_DISJOINTSET_H
