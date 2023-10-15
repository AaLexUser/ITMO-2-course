//
// Created by Alexey Lapin on 4/26/23.
//

#include "TexFile.h"

void TexFile::build() {
    std::ofstream file(fileName);
    file << "\\documentclass{beamer}" << std::endl;
    file << "\\usepackage{tikz}\n" << std::endl;
    file << "\\usepackage{pgfplots}" << std::endl;
    file << "\\usepackage{amsmath}" << std::endl;
    file << "\\usepackage{graphicx}" << std::endl;
    file << "\\usetheme{Pittsburgh}" << std::endl;
    file << "\\begin{document}" << std::endl;
    file << "\\begin{frame}{Graph}" << std::endl;
    file << graph.getAsSring() << std::endl;
    file << "\\end{frame}" << std::endl;
    file << "\\begin{frame}{Table}" << std::endl;
    file << table.getAsSring() << std::endl;
    file << "\\end{frame}" << std::endl;
    file << "\\end{document}" << std::endl;
    file.close();
    system("xelatex --interaction=batchmode Report.tex 2>&1 > /dev/null; open Report.pdf");

}

TexGraph &TexFile::getGraph(){
    return graph;
}

TexTable &TexFile::getTable() {
    return table;
}

void TexFile::buildSeparateOnePdf() {
    graph.build();
    table.build();
    text.build();
    std::ofstream file(fileName);
    file << "\\documentclass{article}" << std::endl;
    file << "\\usepackage{pdfpages}" << std::endl;
    file << "\\begin{document}" << std::endl;
    file <<"\\includepdfset{pages=-,fitpaper=true}" << std::endl;
    file << "\\includepdf[pages=-]{Text.pdf}" << std::endl;
    file << "\\includepdf[pages=-]{Graph.pdf}" << std::endl;
    file << "\\includepdf[pages=-]{Table.pdf}" << std::endl;
    file << "\\includepdfset{}" << std::endl;
    file << "\\end{document}" << std::endl;
    file.close();
    system("xelatex --interaction=batchmode Report.tex 2>&1 > /dev/null; open Report.pdf");
}

TexText &TexFile::getText() {
    return text;
}

void TexFile::buildSeparatePdfs() {
    graph.build();
    table.build();
    text.build();
    system("open graph.pdf");
    system("open table.pdf");
    system("open text.pdf");

}
