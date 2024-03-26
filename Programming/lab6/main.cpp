#include "circle.h"
#include <iostream>

using namespace circle_utility;

int main () {
    Circle c(2, 8, 8);
    Circle c2 (4, 4, 4);
    c.set_point(Point(4, 8)).set_radius(4).set_x(10).set_y(30);
    std::cout << c.info() << std::endl;
    std::cout << circles_surface(c) << std::endl;
    // std::cout << is_belong_to_circle(c, 6, 8) << std::endl;
    // std::cout << c.info() << std::endl;
    // increase_surface(c, 2);
    // std::cout << c.get_point().get_x() << std::endl;
}
