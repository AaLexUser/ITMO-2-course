#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <sstream>
#include "graph/draw/Axis.h"
#include "graph/draw/AxisNumbers.h"
#include "graph/draw/FuncGraph.h"
#include "graph/draw/Grid.h"
#include "graph/draw/IShape.h"
#include "graph/draw/Legend.h"
#include "graph/draw/Points.h"
#include "methods/approximation/ApproximationManager.h"
#include "utils/out/PrintProxy.h"
#include "methods/interpolation/LagrangePolynomial.h"
#include "methods/interpolation/NewtonPolynomial.h"
#include "latex/TexGraph.h"
#include "latex/TexFile.h"
#include "methods/interpolation/StirlingScheme.h"
#include "methods/interpolation/BesselInterpolation.h"

using namespace interpolate_model;

#define printer PrintProxy::getInstance()
std::vector<std::pair<double, double>> loadPointsFromFile(std::string filename) {
    std::vector<std::pair<double, double>> points;
    std::ifstream file(filename);
    if (file.is_open()) {
        double x, y;
        while (file >> x >> y) {
            points.emplace_back(x, y);
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
        throw std::runtime_error("Failed to open file");
    }
    return points;
}

int main() {
    system("osascript -e 'tell application \"Preview\" to quit'");
    std::vector<std::pair<double, double>> points;
    char choice;
    do {
        std::cout << "Do you want to load points from a file/console/function? (1/2/3): ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter 1, 2 or 3.\n" << std::endl;
            continue;
        }
        if (choice == '1') {
            std::string filename;
            std::cout << "Enter _filename: ";
            std::cin >> filename;
            try {
                points = loadPointsFromFile(filename);
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                continue;
            }
            break;
        } else if (choice == '2') {
            int n;
            std::cout << "Enter number of points: ";
            std::cin >> n;
            if (std::cin.fail() || n < 8) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input. Please enter a positive integer 8 or more." << std::endl;
                continue;
            }
            for (int i = 0; i < n; ++i) {
                double x, y;
                std::cout << "Enter x and y for point " << i + 1 << ": ";
                std::cin >> x >> y;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Invalid input. Please enter two numbers." << std::endl;
                    --i;
                    continue;
                }
                points.emplace_back(x, y);
            }
            break;
        } else if(choice == '3') {
            int choice;
            std::unordered_map<int, double(*)( double)> function;
            function[1] = [](double x) { return 1 / (1 + x * x); };
            function[2] = [](double x) { return x*x; };
            function[3] = [](double x) { return 5*x*x*x - 2 * x * x + 3 * x - 15 ; };
            function[4] = [](double x) { return sin(x) ; };
            function[5] = [](double x) { return 1 / sqrt(x); };
            function[6] = [](double x) { return 1 / (1 - x); };
            function[7] = [](double x) { return 1 / abs(1 - x); };
            std::cout << "Choose function:" << std::endl;
            std::cout << "1. 1 / (1 + x * x)" << std::endl;
            std::cout << "2. x^2" << std::endl;
            std::cout << "3. 5x^3 - 2x^2 + 3x - 15" << std::endl;
            std::cout << "4. sin(x)" << std::endl;
            std::cout << "5. 1 / sqrt(x)" << std::endl;
            std::cout << "6. 1 / (1 - x)" << std::endl;
            std::cout << "7. 1 / |1 - x|" << std::endl;
            std::cin >> choice;
            auto func = function[choice];
            std::cout << "Enter the interval [a, b]:" << std::endl;
            double a, b;
            std::cin >> a >> b;
            do {
                std::cout << "Enter the number of points:" << std::endl;
                int count;
                std::cin >> count;
                if (std::cin.fail() || count < 2) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Invalid input. Please enter a positive integer 2 or more." << std::endl;
                    continue;
                }
                if(count >= 2){
                    double step = (b - a) / (count - 1);
                    for (int i = 0; i < count; ++i) {
                        points.emplace_back(a + i * step, func(a + i * step));
                    }
                    break;
                }
            } while (true);
            break;
        }
        else {
            std::cerr << "Invalid input. Please enter y or n." << std::endl;
        }
    } while (true);
    double arg;
    std::cout << "Enter argument: ";
    std::cin >> arg;
    std::string output_choice;
    do {
        std::cout << "Do you want to output to a file? (y/n): ";
        std::cin >> output_choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter y or n.\n" << std::endl;
            continue;
        }
        if (output_choice == "y") {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            printer.toFile(filename);
            break;
        } else if (output_choice == "n") {
            printer.toConsole();
            break;
        } else {
            std::cerr << "Invalid input. Please enter y or n." << std::endl;
        }
    } while (output_choice != "y" && output_choice != "n");
    TexFile texFile;
    std::ostringstream ss;


    ss << std::setprecision(3) << arg;
    texFile.getText().addText("The approximate value of a function for an argument: " + ss.str() + "\n");
    ss.str("");
    LagrangePolynomial lagrange;
    ss <<  std::setprecision(5) << lagrange.predict(points, arg);
    texFile.getText().addText("Lagrange polynomial: " + ss.str() + "\n");
    ss.str("");
    NewtonPolynomial newtonPolinomial;
    ss << std::setprecision(5) << newtonPolinomial.predict(points, arg);
    texFile.getText().addText("Newton polynomial: " + ss.str() + "\n");
    ss.str("");
    StirlingScheme stirling;
    ss << std::setprecision(5) << stirling.predict(points, arg);
    texFile.getText().addText("Stirling polynomial: " + ss.str() + "\n");
    ss.str("");
    BesselInterpolation bessel;
    ss << std::setprecision(5) << bessel.predict(points, arg);
    texFile.getText().addText("Bessel polynomial: " + ss.str() + "\n");
    ss.str("");


    texFile.getGraph().addPointEntry("Points", points);
    std::cout << "===========[Debug INFO]====================" << std::endl;
    std::cout << "===========[Raw Funtions]==================" << std::endl;
    std::cout << "===========[Newton]========================" << std::endl;
    std::cout <<newtonPolinomial.getFunctionAsString(points)<<std::endl;
    std::cout << "===========[Lagrange]======================" << std::endl;
    std::cout << lagrange.getFunctionAsString(points)<<std::endl;
    std::cout << "===========[Stirling]======================" << std::endl;
    std::cout << stirling.getFunctionAsString(points)<<std::endl;
    std::cout << "===========[Bessel]========================" << std::endl;
    std::cout << bessel.getFunctionAsString(points)<<std::endl;
    texFile.getGraph().addFunctionEntry("Newton", newtonPolinomial.getFunctionAsString(points));
    texFile.getGraph().addFunctionEntry("Lagrange", lagrange.getFunctionAsString(points));
//    texFile.getGraph().addFunctionEntry("Stirling", stirling.getFunctionAsString(points));
//    texFile.getGraph().addFunctionEntry("Bessel", bessel.getFunctionAsString(points));
    std::vector<std::vector<double>> differences;
    Math::calculateFinalDifferencesMatrix(points, differences);
    Math::T(differences);
    std::vector<std::string> row = {"№", "$x_i$", "$y_i$", "$\\Delta y_i$"};
    for(int i = 2; i < points.size(); ++i) {
        row.emplace_back("$\\Delta^{" + std::to_string(i) + "} y_i$");
    }
    texFile.getTable().addRow(row);
    for(int i = 0; i < points.size(); ++i) {
        std::vector<std::string> row;
        std::ostringstream ss;
        row.emplace_back(std::to_string(i));
        ss << std::setprecision(3) << points[i].first;
        row.emplace_back(ss.str());
        ss.str("");
        ss << std::setprecision(3) << points[i].second;
        row.emplace_back(ss.str());
        for(int j = 1; j < points.size(); ++j) {
            if(differences[i][j] == 0 || (differences[i][j] > -10e-9 && differences[i][j] < 10e-9)){
                if(j >= points.size() - i){
                    row.emplace_back("");
                }
                else {
                    ss.str("");
                    ss << std::setprecision(3) << differences[i][j];
                    row.emplace_back(ss.str());
                }
            }
            else if(differences[i][j] == (int)differences[i][j])
                row.emplace_back(std::to_string((int)differences[i][j]));
            else {
                ss.str("");
                ss << std::setprecision(3) << differences[i][j];
                row.emplace_back(ss.str());
            }
        }
        texFile.getTable().addRow(row);
    }
    texFile.getTable().addCaption("Finite Difference Table");
    texFile.buildSeparateOnePdf();
    return 0;

}
