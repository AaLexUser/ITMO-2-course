#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "graph/draw/Axis.h"
#include "graph/draw/AxisNumbers.h"
#include "graph/draw/FuncGraph.h"
#include "graph/draw/Grid.h"
#include "graph/draw/IShape.h"
#include "graph/draw/Legend.h"
#include "graph/draw/Points.h"
#include "methods/approximation/ApproximationManager.h"
#include "utils/out/PrintProxy.h"

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
    std::vector<std::pair<double, double>> points;
    char choice;
    do {
        std::cout << "Do you want to load points from a file? (y/n): ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter y or n.\n" << std::endl;
            continue;
        }
        if (choice == 'y') {
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
        } else if (choice == 'n') {
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
        } else {
            std::cerr << "Invalid input. Please enter y or n." << std::endl;
        }
    } while (true);
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

    std::vector<std::unique_ptr<IShape>> shapes;
    shapes.push_back(std::make_unique<Axis>(3));
    shapes.push_back(std::make_unique<AxisNumbers>());
    shapes.push_back(std::make_unique<Grid>(1));
    ApproximationManager manager(points);
    Legend legend;
    legend.addEntry("Points", sf::Color::Red);
    std::vector<sf::Color> colors = {sf::Color(156, 89, 0), sf::Color(5, 156, 0), sf::Color::Blue, sf::Color(225,167,18), sf::Color::Magenta, sf::Color::Cyan};
    ApproximationEnum best_approximation;
    double min_sd = 100;
    for (auto &approx : manager.getApproximations()) {
        std::string str = approximation_str[approx.first];
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        approx.second->fit();
        if(!std::isnan(approx.second->getParams()[0])) {
            printer << std::string(10, '-') << str << std::string(10, '-') << "\n";
            ctable << approx.second->get_info();
            ctable << approx.second->get_extras_info();
            shapes.push_back(std::make_unique<FuncGraph>(approx.second->getF(), approx.second->getParams(), 10,
                                                         colors[approx.first]));
            legend.addEntry(approximation_str[approx.first], colors[approx.first]);
            if (approx.second->get_extra_info("Standard Deviation") < min_sd) {
                min_sd = approx.second->get_extra_info("Standard Deviation");
                best_approximation = approx.first;
            }
        }
    }
    printer << std::string(10, '-') << "BEST APPROXIMATION" << std::string(10, '-') << "\n";
    printer << "Best approximation: " << approximation_str[best_approximation] << "\n";
    printer << "Standard Deviation: " << min_sd << "\n";
    printer.toConsole();
    shapes.push_back(std::make_unique<Legend>(legend));
    sf::Color customBlue(100, 150, 255);
    shapes.push_back(std::make_unique<Points>(points, sf::Color::Red));
    MainWindow::getInstance().setShapes(shapes);
    MainWindow::getInstance().display();

    return 0;

}
