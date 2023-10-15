//
// Created by Alexey Lapin on 4/26/23.
//

#ifndef COMPLMATH5_TEXTEXT_H
#define COMPLMATH5_TEXTEXT_H

#include <iostream>
#include <fstream>
#include <vector>
class TexText {
public:
    TexText() {
        fileName = "text.tex";
    }

    void addText(const std::string &text);

    void build();

    std::string getAsSring();
private:
    std::ofstream _file;
    std::string fileName;
    std::vector<std::string> _textEntries;
};


#endif //COMPLMATH5_TEXTEXT_H
