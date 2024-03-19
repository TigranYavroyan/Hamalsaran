#include "circle.h"
#include <iostream>

int main () {
    Circle c(2, 8, 8);
    Circle c2 (4, 4, 4);
    std::cout << is_belong_to_circle(c, 6, 8) << std::endl;
    std::cout << c.info() << std::endl;
    increase_surface(c, 2);
}
