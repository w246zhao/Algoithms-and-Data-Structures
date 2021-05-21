//
// Created by Wendi Zhao on 2020/9/27.
//

#ifndef ECE250_PROJECT1_OPENHT_H
#define ECE250_PROJECT1_OPENHT_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class openHashTable{
public:
    openHashTable();
    ~openHashTable();

    void set_size(unsigned int size);

    void insert_term( std::string &number, std::string name);

    void delete_term(std::string number);

    long int search_term (std::string &number);

    bool table_is_full() const;

    std::string name(unsigned int index);

private:
    std::vector <long long int> keys;
    std::vector <std::string> names;
    unsigned int table_size;
    unsigned int curr_size;
};


openHashTable::openHashTable() {
    table_size = 0;
    curr_size = 0;
}

openHashTable::~openHashTable() {
    keys = std::vector<long long int>();
    names = std::vector<std::string>();
}

void openHashTable::set_size(unsigned int size) {
    keys.resize(size, 0);
    names.resize(size, "");
    table_size = size;
    curr_size = 0;
}

void openHashTable::insert_term( std::string &number, std::string name) {
    unsigned int probe;
    unsigned int offset;

    if (table_is_full()){
        std::cout<<"failure"<<std::endl;
        return;
    }

    if (search_term(number) > -1 && curr_size != 0){
        std::cout<<"failure"<<std::endl;
        return;
    }

    probe = (std::stoll(number) % table_size);
    offset = (unsigned int)floor((double)std::stoll(number) / (double)table_size) % table_size;
    offset += (offset % 2);

    while (keys[probe] != 0 && keys[probe] != 1){
        probe = (probe+offset) %table_size;
    }
    keys[probe] = stoll(number);
    names[probe] = name;
    std::cout<<"success"<<std::endl;
    curr_size++;
}

void openHashTable::delete_term(std::string number) {
    if (curr_size == 0){
        std::cout<<"failure"<<std::endl;
        return;
    }
    long int index = search_term(number);
    if (index > -1){
        keys[index] = 1;
        curr_size--;
        std::cout<<"success"<<std::endl;
    }
    else{
        std::cout<<"failure"<<std::endl;
    }
}

long int openHashTable::search_term(std::string &number) {
    unsigned int probe;
    unsigned int original_index;
    unsigned int offset;

    if (curr_size == 0){
        return -1;
    }
    probe = (std::stoll(number) % table_size);
    original_index = probe;
    offset = (unsigned int)floor((double)std::stoll(number) / (double)table_size) % table_size;
    offset += (offset % 2);

    while (keys[probe] != stoll(number)){
        if (keys[probe] == 0){
            return -1;
        }
        probe = (probe+offset) %table_size;
        //table is full and all indices have been check
        if (original_index == probe){
            return -1;
        }
    }
    return probe;
}

bool openHashTable::table_is_full() const {
    return (curr_size == table_size);
}

std::string openHashTable::name(unsigned int index) {
    return (names[index]);
}



#endif //ECE250_PROJECT1_OPENHT_H
