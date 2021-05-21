//
// Created by Wendi Zhao on 2020/10/17.
//
#include "Quadtree.h"
#include <iostream>
#include <string>

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

    std::string name;
    long long pop;
    double y_lat;
    double x_long;
    double cost;
    double salary;

    Quadtree quadtree;

    getline(std::cin, cmdline);

    while (!std::cin.eof()){
        if (cmdline == "exit"){
            return 0;
        }

        //commands that don't require any input parsing
        if (cmdline == "print"){
            quadtree.print();
            getline(std::cin, cmdline);
            continue;
        }

        if (cmdline == "clear"){
            quadtree.clear();
            getline(std::cin, cmdline);
            continue;
        }

        if (cmdline == "size"){
            quadtree.size();
            getline(std::cin, cmdline);
            continue;
        }


        //split the input by space to find the command (commands that require input parsing)
        unsigned long index = cmdline.find(' ');

        if (index!= std::string::npos){
            cmd = cmdline.substr(0, index);
            cmdline = cmdline.substr(index+1);


            if (cmd == "i"){
                std::string split;
                split_semi(cmdline, split);
                name = split;

                split_semi(cmdline, split);
                x_long = std::stod(split);

                split_semi(cmdline, split);
                y_lat = std::stod(split);

                split_semi(cmdline, split);
                pop = std::stoll(split);

                split_semi(cmdline, split);
                cost = std::stod(split);

                salary = std::stod(cmdline);

                quadtree.insert(x_long, y_lat, pop, cost, salary, name);
            }

            else if (cmd == "s"){
                std::string split;
                split_semi(cmdline, split);
                x_long = std::stod(split);

                y_lat = std::stod(cmdline);

                quadtree.search(x_long, y_lat);
            }

            else if (cmd == "q_max"){
                std::string split;
                std::string dir;

                split_semi(cmdline, split);
                x_long = std::stod(split);

                split_semi(cmdline, split);
                y_lat = std::stod(split);

                split_semi(cmdline, split);
                dir = split;

                char attr = cmdline.at(0);

                quadtree.q_max(x_long, y_lat, dir, attr);
            }

            else if (cmd == "q_min"){
                std::string split;
                std::string dir;

                split_semi(cmdline, split);
                x_long = std::stod(split);

                split_semi(cmdline, split);
                y_lat = std::stod(split);

                split_semi(cmdline, split);
                dir = split;

                char attr = cmdline.at(0);

               quadtree.q_min(x_long, y_lat, dir, attr);
            }

            else if (cmd == "q_total"){
                std::string split;
                std::string dir;

                split_semi(cmdline, split);
                x_long = std::stod(split);

                split_semi(cmdline, split);
                y_lat = std::stod(split);

                split_semi(cmdline, split);
                dir = split;

                char attr = cmdline.at(0);

                quadtree.q_total(x_long, y_lat, dir, attr);
            }
        }
        getline(std::cin, cmdline);
    }
}