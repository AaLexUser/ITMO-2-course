//
// Created by Alexey Lapin on 4/25/23.
//

#ifndef COMPLMATH5_TEXGRAPH_H
#define COMPLMATH5_TEXGRAPH_H

#include <iostream>
#include <fstream>
class TexGraph {
public:
    TexGraph(){
        fileName = "graph.tex";
    }
    void addPointEntry(const std::string & name, const std::vector<std::pair<double, double>> & points);
    void addCaption(const std::string & caption);
    void addFunctionEntry(const std::string & name, const std::string & function);
    void build();
    std::string getAsSring();
private:
    std::ofstream _file;
    std::string fileName;
    std::string _caption;
    std::vector<std::pair<std::string, std::vector<std::pair<double, double>>>> _pointsEnries;
    std::vector<std::pair<std::string, std::string>> _functionEntries;

};


#endif //COMPLMATH5_TEXGRAPH_H
