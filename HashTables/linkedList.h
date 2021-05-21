//
// Created by Wendi Zhao on 2020/10/3.
//

#ifndef ECE250_PROJECT1_LINKEDLIST_H
#define ECE250_PROJECT1_LINKEDLIST_H

#include <iostream>
#include <string>
#include <cmath>

struct node{
    long long int key;
    std::string value;
    node *next;
};


class linkedList{
public:
    linkedList();

    ~linkedList();

    void insert_term(std::string &number, std::string &name);

    void delete_term(std::string &number);

    void search(std::string &number, int index);

    void print_list();

private:
    node *head;
};

linkedList::linkedList() {
    head = nullptr;
}

//destructor
//steps through link list and deletes all allocated memory
linkedList::~linkedList() {
    if (head != nullptr){
        node *current = head->next;
        node *previous = nullptr;
        while (current!= nullptr){
            previous = current;
            current = current->next;
            delete previous;
            previous = nullptr;
        }
        delete head;
        head = nullptr;
    }
}

void linkedList::insert_term(std::string &number, std::string &name) {
    node *current = head;
    node *previous = nullptr;
    long long int converted_number = std::stoll(number);
    if (current == nullptr){
        node *tmp = new node;
        tmp -> key = converted_number;
        tmp -> value = name;
        tmp -> next = nullptr;
        head = tmp;
        tmp = nullptr;
        std::cout<<"success"<<std::endl;
        return;
    }
    while (current != nullptr){
        if (current->key == converted_number){
            std::cout<<"failure"<<std::endl;
            return;
        }
        if (current->key > converted_number){
            node *tmp = new node;
            tmp -> key = converted_number;
            tmp -> value = name;
            if (previous == nullptr){
                tmp->next = current;
                head = tmp;
            }
            else{
                previous->next = tmp;
                tmp->next = current;
            }
            tmp = nullptr;
            std::cout<<"success"<<std::endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    node *tmp = new node;
    tmp -> key = converted_number;
    tmp -> value = name;
    tmp -> next = nullptr;
    previous->next = tmp;
    std::cout<<"success"<<std::endl;
    tmp = nullptr;
}

void linkedList::delete_term(std::string &number) {
    node *current = head;
    node *previous = nullptr;
    long long int converted_number = std::stoll(number);
    while (current != nullptr){
        if (current->key == converted_number){
            if (previous == nullptr){
                head = current->next;
                delete current;
                current = nullptr;
            }
            else{
                previous->next=current->next;
                delete current;
                current = nullptr;
            }
            std::cout<<"success"<<std::endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    std::cout<<"failure"<<std::endl;
}

void linkedList::search(std::string &number, int index) {
    node *current = head;
    long long int converted_number = std::stoll(number);
    while (current != nullptr){
        if (current->key == converted_number){
            std::cout<<"found "<<current->value<<" in "<<index<<std::endl;
            return;
        }
        current = current -> next;
    }
    std::cout<<"not found"<<std::endl;
    current = nullptr;
}

void linkedList::print_list() {
    node *current = head;
    bool found = false;
    while (current!= nullptr){
        if (!found){
            std::cout<<current->key;
        }
        else{
            std::cout<<" "<<current->key;
        }
        current = current->next;
        found = true;
    }
    if (found){
        std::cout<<std::endl;
    }
}


#endif //ECE250_PROJECT1_LINKEDLIST_H
