#include "point.h"

Point::Point (double x) : m_x{x} {}

Point::Point (double x, double y) : m_x{x}, m_y{y} {}

void Point::set_x (double x) {
    m_x = x;
}

void Point::set_x_y (double x, double y) {
    m_x = x;
    m_y = y;
}

double Point::get_x () const {
    return m_x;
}

double Point::get_y () const {
    return m_y;
}