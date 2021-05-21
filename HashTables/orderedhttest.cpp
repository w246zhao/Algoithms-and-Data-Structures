//
// Created by Wendi Zhao on 2020/9/27.
//
#include "orderedht.h"
#include <iostream>
#include <string>


int main(){
    std::string cmdline;
    std::string cmd;

    std::string number;
    std::string name;

    orderedHashTable hashTable;

    getline(std::cin, cmdline);

    while (!std::cin.eof()){
        if (cmdline == "exit"){
            return 0;
        }

        //split the input by space to find the command
        unsigned long index = cmdline.find(' ');

        if (index!= std::string::npos){
            cmd = cmdline.substr(0, index);
            cmdline = cmdline.substr(index+1);


            if (cmd == "n"){
                hashTable.resize_table(stoi(cmdline));
                std::cout<<"success"<<std::endl;
            }

            else if (cmd == "i"){
                index = cmdline.find(';');
                if (index != std::string::npos){
                    number = cmdline.substr(0,index);
                    name = cmdline.substr(index+1);
                }
                hashTable.insert_term(number, name);
            }

            else if (cmd == "s"){
                hashTable.search_term(cmdline);
            }

            else if (cmd == "d"){
                hashTable.delete_term(cmdline);
            }

            else if (cmd == "p"){
                hashTable.print_terms_at_index(std::stoi(cmdline));
            }
        }
        getline(std::cin, cmdline);
    }
}