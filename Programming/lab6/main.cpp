#include "circle.h"
#include <iostream>

int main () {
    Circle c(2, 2, 2);
    Circle c2 (4, 4, 4);
    std::cout << is_belong_to_circle(c, 8, 3) << std::endl;
    std::cout << c.info() << std::endl;
    try {increase_surface(c, 2);}
    catch(std::exception& e){std::cout << circles_surface(c) << std::endl;}
}
