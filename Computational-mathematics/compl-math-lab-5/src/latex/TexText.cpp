//
// Created by Alexey Lapin on 4/26/23.
//

#include "TexText.h"

void TexText::addText(const std::string &text) {
    _textEntries.push_back(text);
}

void TexText::build() {
    std::ofstream file(fileName);
    file << "\\documentclass{beamer}" << std::endl;
    file << "\\usepackage{tikz}\n" << std::endl;
    file << "\\usepackage{pgfplots}" << std::endl;
    file << "\\usepackage{amsmath}" << std::endl;
    file << "\\usepackage{graphicx}" << std::endl;
    file << "\\usetheme{CambridgeUS}"<< std::endl;
    file << "\\begin{document}" << std::endl;
    file <<"\\begin{frame}{Approximate value}" << std::endl;
    for (auto text : _textEntries) {
        file << text << "\\\\" << std::endl;
    }
    file << "\\end{frame}" << std::endl;
    file << "\\end{document}" << std::endl;
    file.close();
    system("xelatex --interaction=batchmode text.tex 2>&1 > /dev/null;");
}
