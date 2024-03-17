#include "Polynom.h"
#include <iostream>

int main () {
    std::vector<double> coef = {1.2, -2.5, 3.7, 4.4, 5.6, 6.7};
    std::vector<int> deg = {6, 5, 4, 1, 2, 1};
    Polynom jan(coef, deg, 'y');
    jan.display();
    Polynom jan2 = calcDerivative(jan, 2);
    jan2.display();
    std::cout << calcPolynom(jan2, 2);
}
