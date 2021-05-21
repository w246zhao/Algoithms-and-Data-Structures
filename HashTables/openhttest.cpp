//
// Created by Wendi Zhao on 2020/9/27.
//

#include "openht.h"
#include <iostream>
#include <string>


int main(){
    std::string cmdline;
    std::string cmd;

    std::string number;
    std::string name;

    openHashTable hashTable;

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
                hashTable.~openHashTable();
                hashTable.set_size(stoi(cmdline));
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
                long int term_index = hashTable.search_term(cmdline);
                if (term_index<0){
                    std::cout<<"not found"<<std::endl;
                }
                if (term_index>-1){
                    std::cout<<"found "<<hashTable.name(term_index)<<" in "<<term_index<<std::endl;
                }
            }

            else if (cmd == "d"){
                hashTable.delete_term(cmdline);
            }
        }
        getline(std::cin, cmdline);
    }
}