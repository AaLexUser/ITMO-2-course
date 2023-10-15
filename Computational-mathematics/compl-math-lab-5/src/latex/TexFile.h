//
// Created by Alexey Lapin on 4/26/23.
//

#ifndef COMPLMATH5_TEXFILE_H
#define COMPLMATH5_TEXFILE_H


#include "TexGraph.h"
#include "TexTable.h"
#include "TexText.h"

class TexFile {
    TexGraph graph;
    TexTable table;
    TexText text;
public:
    TexFile(){
        fileName = "Report.tex";
    }

    TexGraph &getGraph();
    TexTable &getTable();
    TexText &getText();

    void build();
    void buildSeparateOnePdf();
    void buildSeparatePdfs();
private:
    std::string fileName;
};


#endif //COMPLMATH5_TEXFILE_H
