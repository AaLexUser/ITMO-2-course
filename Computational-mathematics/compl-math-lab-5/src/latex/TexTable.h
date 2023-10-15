//
// Created by Alexey Lapin on 4/26/23.
//

#ifndef COMPLMATH5_TEXTABLE_H
#define COMPLMATH5_TEXTABLE_H

#include <iostream>
#include <fstream>
#include <vector>

class TexTable {
public:
    TexTable(){
        fileName = "table.tex";
    }
    void addRow(const std::vector<std::string> & row);
    void addCaption(const std::string & caption);
    void addRow(const std::vector<double> & row);
    void build();
    std::string getAsSring();
private:
    std::ofstream _file;
    std::string _caption;
    std::string fileName;
    std::vector<std::vector<std::string>> _rows;

};


#endif //COMPLMATH5_TEXTABLE_H
