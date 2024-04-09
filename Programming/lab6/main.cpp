#include "circle.h"
#include <iostream>

using namespace circle_utility;

int main () {
    Point obj(3, 5);
    Circle c(2, 8, 8);
    Circle c2 = c;
    std::cout << c << std::endl;
    std::cout << c2 << std::endl;
    // std::cout << is_belong_to_circle(c, 6, 8) << std::endl;
    // std::cout << c.info() << std::endl;
    // increase_surface(c, 2);
    // std::cout << c.get_point().get_x() << std::endl;
}
