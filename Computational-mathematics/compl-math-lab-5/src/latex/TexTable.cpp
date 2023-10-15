//
// Created by Alexey Lapin on 4/26/23.
//

#include "TexTable.h"

void TexTable::addRow(const std::vector<std::string> &row) {
    _rows.push_back(row);
}

std::string TexTable::getAsSring() {
    std::string result = "\\begin{table}[h]\n";
    result += "\\centering\n";
    result += "\\caption{" + _caption + "}\n";
    result += "\\label{tab:my_label}\n";
    result += "\\begin{tabular}{|";
    for (int i = 0; i < _rows[0].size(); ++i) {
        result += "c|";
    }
    result += "}\n";
    result += "\\hline\n";
    for (int i = 0; i < _rows.size(); ++i) {
        for (int j = 0; j < _rows[i].size(); ++j) {
            result += _rows[i][j];
            if (j != _rows[i].size() - 1) {
                result += " & ";
            }
        }
        result += " \\\\ \\hline\n";
    }
    result += "\\end{tabular}\n";
    result += "\\end{table}\n";
    return result;
}

void TexTable::addCaption(const std::string &caption) {
    _caption = caption;
}

void TexTable::build() {
    std::ofstream file(fileName);
    file << "\\documentclass[border=5pt]{standalone}" << std::endl;
    file << "\\usepackage{tikz}\n" << std::endl;
    file << "\\usepackage{pgfplots}" << std::endl;
    file << "\\usepackage{amsmath}" << std::endl;
    file << "\\usepackage{graphicx}" << std::endl;
    file << "\\begin{document}" << std::endl;
    file << "\\centering" << std::endl;
    file << "Finite difference method" << std::endl;
    file << "\\begin{tabular}{|";
    for (int i = 0; i < _rows[0].size(); ++i) {
        file << "c|";
    }
    file << "}\n";
    file << "\\hline\n";
    for (int i = 0; i < _rows.size(); ++i) {
        for (int j = 0; j < _rows[i].size(); ++j) {
            file << _rows[i][j];
            if (j != _rows[i].size() - 1) {
                file << " & ";
            }
        }
        file << " \\\\ \\hline\n";
    }
    file << "\\end{tabular}\n";
    file << "\\end{document}" << std::endl;
    file.close();
    system("xelatex --interaction=batchmode table.tex 2>&1 > /dev/null");


}
