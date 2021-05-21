//
// Created by Wendi Zhao on 2020/9/27.
//

#ifndef ECE250_PROJECT1_ORDEREDHT_H
#define ECE250_PROJECT1_ORDEREDHT_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "linkedList.h"

class orderedHashTable{
public:

    orderedHashTable();

    ~orderedHashTable();

    void resize_table(int size);

    void insert_term(std::string &number, std::string name);

    void delete_term(std::string &number);

    void search_term (std::string &number);

    void print_terms_at_index(int index);

private:
    std::vector <linkedList> linkedLists;
    unsigned int table_size;
};

orderedHashTable::orderedHashTable() {
    table_size = 0;
    linkedLists.resize(0);
}


orderedHashTable::~orderedHashTable() {
    for (int i = 0; i < table_size; i++){
        linkedLists[i].~linkedList();
    }
}

void orderedHashTable::resize_table(int size) {
    for (int i = 0; i < table_size; i++){
        linkedLists[i].~linkedList();
    }
    table_size = size;
    linkedLists.resize(size);
}


void orderedHashTable::insert_term(std::string &number, std::string name) {
    unsigned int probe;

    probe = (std::stoll(number) % table_size);

    linkedLists[probe].insert_term(number, name);
}

void orderedHashTable::delete_term(std::string &number) {
    unsigned int probe;

    probe = (std::stoll(number) % table_size);

    linkedLists[probe].delete_term(number);
}

void orderedHashTable::search_term(std::string &number) {
    unsigned int probe;

    probe = (std::stoll(number) % table_size);

    linkedLists[probe].search(number, probe);
}

void orderedHashTable::print_terms_at_index(int index) {
    if (index >= 0 && index < table_size){
        linkedLists[index].print_list();
    }
}


#endif //ECE250_PROJECT1_ORDEREDHT_H
