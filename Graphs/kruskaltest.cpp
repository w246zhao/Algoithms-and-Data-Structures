//
// Created by Wendi Zhao on 2020/11/22.
//

#include <iostream>
#include "graph.h"

void split_semi(std::string &info, std::string & separated){
    int index = info.find(';');
    if (index!= std::string::npos){
        separated = info.substr(0, index);
        info = info.substr(index+1);
    }
}

int main(){
    std::string cmdline;
    std::string cmd;

    Graph kruskal;

    getline(std::cin, cmdline);

    while (!std::cin.eof()){
        if (cmdline == "exit"){
            return 0;
        }

        //commands that don't require any input parsing
        if (cmdline == "clear"){
            kruskal.clear();
            getline(std::cin, cmdline);
            continue;
        }

        if (cmdline == "edge_count"){
            kruskal.edge_count();
            getline(std::cin, cmdline);
            continue;
        }

        if (cmdline == "mst"){
            kruskal.mst();
            getline(std::cin, cmdline);
            continue;
        }

        //split the input by space to find the command (commands that require input parsing)
        unsigned long index = cmdline.find(' ');

        if (index!= std::string::npos){
            cmd = cmdline.substr(0, index);
            cmdline = cmdline.substr(index+1);

            if (cmd == "n"){
                int m = std::stoi(cmdline);
                try {
                    kruskal.resize(m);
                }
                catch (illegal_argument& e) {
                    std::cout<<e.what()<<std::endl;
                }
            }

            if (cmd == "i"){
                std::string split;
                split_semi(cmdline, split);
                int u = std::stoi(split);

                split_semi(cmdline, split);
                int v = std::stoi(split);

                double w = std::stod(cmdline);

                try {
                    kruskal.insert(u, v, w);
                }
                catch (illegal_argument& e) {
                    std::cout<<e.what()<<std::endl;
                }
            }

            else if (cmd == "d"){
                std::string split;
                split_semi(cmdline, split);
                int u = std::stoi(split);

                int v = std::stoi(cmdline);

                try {
                    kruskal.delete_edge(u, v);
                }
                catch (illegal_argument& e) {
                    std::cout<<e.what()<<std::endl;
                }
            }

            else if (cmd == "degree"){
                int u = std::stoi(cmdline);
                try {
                    kruskal.degree(u);
                }
                catch (illegal_argument& e) {
                    std::cout<<e.what()<<std::endl;
                }
            }
        }
        getline(std::cin, cmdline);
    }
}
