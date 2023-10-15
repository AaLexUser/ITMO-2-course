//
// Created by Alexey Lapin on 4/25/23.
//

#include "TexGraph.h"
#include <algorithm>
void TexGraph::build() {
    std::ofstream file(fileName);
    std::vector<std::pair<double,double>> & interPoints = _pointsEnries.front().second;
    double h = (_pointsEnries.front().second.back().first - _pointsEnries.front().second.front().first) / (_pointsEnries.front().second.size() - 1);
    file << "\\documentclass[border=5pt]{standalone}" << std::endl;
    file << "\\usepackage{tikz}" << std::endl;
    file << "\\usepackage{pgfplots}" << std::endl;
    file << "\\begin{document}" << std::endl;
    file << "\\begin{tikzpicture}" << std::endl;
    file << "\\begin{axis}[" << std::endl;
    file << "axis lines=center," << std::endl;
    file << "xlabel=$x$," << std::endl;
    file << "ylabel=$y$," << std::endl;
    file << "width=\\textwidth," << std::endl;
    double padding = h;
    auto&& [xmin, xmax] = std::minmax_element(interPoints.begin(), interPoints.end());
    file << "xmax=" <<xmax->first+ padding << "," << std::endl;
    file << "xmin=" << xmin->first - padding << "," << std::endl;
    auto&& [ymin, ymax] = std::minmax_element(interPoints.begin(), interPoints.end(), [](const auto & a, const auto & b) {
        return a.second < b.second;
    });
    file << "ymax=" << ymax->second + padding << "," << std::endl;
    file << "ymin=" << ymin->second - padding << "," << std::endl;
    file << "grid=both," << std::endl;
    file << "minor tick num=5," << std::endl;
    file << "domain=" <<_pointsEnries.front().second.front().first - h <<":"<<_pointsEnries.front().second.back().first + h  << "," << std::endl;
    file << "smooth," << std::endl;
    file << "legend pos=north west," << std::endl;
    file << "legend cell align=left," << std::endl;
    file << "legend style={at={(0.5,-0.1)},anchor=north}," << std::endl;
    file << "]" << std::endl;
    for (const auto &[name, points] : _pointsEnries) {
        file << "\\addplot+[only marks] coordinates {";
        for (const auto &[x, y] : points) {
            file << "(" << x << "," << y << ")";
        }
        file << "};" << std::endl;
        file << "\\addlegendentry{" << name << "}" << std::endl;
    }
    for(const auto &[name, funtion] : _functionEntries) {
        file << "\\addplot+[no markers] {" << funtion << "};" << std::endl;
        file << "\\addlegendentry{" << name << "}" << std::endl;
    }
    file << "\\end{axis}" << std::endl;
    file << "\\end{tikzpicture}" << std::endl;
    file << "\\end{document}" << std::endl;
    file.close();
    system("xelatex --interaction=batchmode graph.tex 2>&1 > /dev/null");
}

void TexGraph::addPointEntry(const std::string &name, const std::vector<std::pair<double, double>> &points) {
    _pointsEnries.emplace_back(name, points);
}

void TexGraph::addFunctionEntry(const std::string &name, const std::string &function) {
    _functionEntries.emplace_back(name, function);
}

std::string TexGraph::getAsSring() {
    std::string str = "";
    std::vector<std::pair<double,double>> & interPoints = _pointsEnries.front().second;
    double h = (_pointsEnries.front().second.back().first - _pointsEnries.front().second.front().first) / (_pointsEnries.front().second.size() - 1);
    str += "\\begin{tikzpicture}\n";
    str += "\\begin{axis}[\n";
    str += "axis lines=center,\n";
    str += "xlabel=$x$,\n";
    str += "ylabel=$y$,\n";
    str += "width=\\textwidth,\n";
    str += "grid=both,\n";
    double padding = h;
    auto&& [xmin, xmax] = std::minmax_element(interPoints.begin(), interPoints.end());
    str += "xmax=" + std::to_string(xmax->first+ padding) + ",\n";
    str += "xmin=" + std::to_string(xmin->first - padding) + ",\n";
    auto&& [ymin, ymax] = std::minmax_element(interPoints.begin(), interPoints.end(), [](const auto & a, const auto & b) {
        return a.second < b.second;
    });
    str += "ymax=" + std::to_string(ymax->second + padding) + ",\n";
    str += "ymin=" + std::to_string(ymin->second - padding) + ",\n";
    str += "minor tick num=5,\n";

    str += "domain=" + std::to_string(_pointsEnries.front().second.front().first - h) + ":" + std::to_string(_pointsEnries.front().second.back().first + h) + ",\n";
    str += "smooth,\n";
    str += "legend cell align=left,\n";
    str += "legend style={at={(" + std::to_string(_pointsEnries.front().second.back().first * 2) +"," + std::to_string(_pointsEnries.front().second.front().second/2) +  ")},anchor=north},\n";
    str += "]\n";
    for (const auto &[name, points] : _pointsEnries) {
        str += "\\addplot+[only marks] coordinates {";
        for (const auto &[x, y] : points) {
            str += "(" + std::to_string(x) + "," + std::to_string(y)+ ")";
        }
        str += "};\n";
        str += "\\addlegendentry{" + name + "}\n";
    }
    for(const auto &[name, funtion] : _functionEntries) {
        str += "\\addplot+[no markers] {" + funtion + "};\n";
        str += "\\addlegendentry{" + name + "}\n";
    }
    str += "\\end{axis}\n";
    str += "\\end{tikzpicture}";
    return str;
}
