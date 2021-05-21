//
// Created by Wendi Zhao on 2020/11/22.
//

#include "disjointSet.h"
disjointSet::disjointSet(int sets) {
    totalSets = sets;
    set = new LinkedList[sets];
    for (int i = 0; i < sets; i++){
        makeSet(i);
    }
}

disjointSet::~disjointSet() {
    for(int i = 0; i < totalSets; i++) {
        if(set[i].headptr != nullptr)
            delete set[i].headptr;
    }
    delete[] set;
}

void disjointSet::makeSet(int x) {
    node* element = new node;
    element->next = nullptr;
    element->value = x;
    element->representative = &set[x];
    set[x].headptr = element;
    set[x].tailptr = element;
    set[x].length = 1;
}

int disjointSet::findSet(int n) {
    return set[n].headptr->representative->headptr->value;
}

void disjointSet::combineSet(int x, int y) {
    if (x==y){
        return;
    }

    int x_length = set[x].headptr->representative->length;
    int y_length = set[y].headptr->representative->length;

    LinkedList* listToCopy;
    LinkedList* listToKeep;
    if (x_length<y_length){
        listToCopy =  set[x].headptr->representative;
        listToKeep =  set[y].headptr->representative;
    }
    else{
        listToCopy =  set[y].headptr->representative;
        listToKeep =  set[x].headptr->representative;
    }

    listToKeep->tailptr->next= listToCopy->headptr;
    node *tmp = listToCopy->headptr;
    while (tmp != nullptr){
        tmp->representative=listToKeep;
        tmp=tmp->next;
    }

    listToKeep->tailptr=listToCopy->tailptr;
    listToKeep->length+=listToCopy->length;
}