#include "Rational.h"
#include <iostream>
#include <locale>

int main() {
    std::locale::global(std::locale(""));

    int choice;
    std::cout << "Choose equation type:\n"
        << "1 - Linear equation (a*x + b = 0)\n"
        << "2 - Quadratic equation (a*x^2 + b*x + c = 0)\n"
        << "Your choice: ";
    std::cin >> choice;

    try {
        switch (choice) {
        case 1:
            solveLinearEquation();
            break;
        case 2:
            solveQuadraticEquation();
            break;
        default:
            std::cout << "Invalid choice\n";
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
