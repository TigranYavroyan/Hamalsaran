#include "point.h"

#include <limits>

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

Point& Point::operator-- () {
    --m_x;
    --m_y;
    return *this;
}

Point Point::operator-- (int) {
    Point tmp = *this;
    --(*this);
    return tmp;
}

Point& Point::operator++ () {
    ++m_x;
    ++m_y;
    return *this;
}

Point Point::operator++ (int) {
    Point tmp = *this;
    ++(*this);
    return tmp;
}

Point operator+ (const Point& lhv, const Point& rhv) {
    return Point(lhv.get_x() + rhv.get_x(), lhv.get_y() + rhv.get_y());
}

Point operator- (const Point& lhv, const Point& rhv) {
    return Point(lhv.get_x() - rhv.get_x(), lhv.get_y() - rhv.get_y());
}

Point& operator+= (Point& lhv, const Point& rhv) {
    lhv = lhv + rhv;
    return lhv;
}

Point& operator-= (Point& lhv, const Point& rhv) {
    lhv = lhv - rhv;
    return lhv;
}

bool operator== (const Point& lhv, const Point& rhv) {
    return (lhv.get_x() == rhv.get_x() && lhv.get_y() == rhv.get_y());
}

bool operator!= (const Point& lhv, const Point& rhv) {
    return !(lhv == rhv);
}

bool operator< (const Point& lhv, const Point& rhv) {
    return ((lhv != rhv) && lhv.get_x() + lhv.get_y()) < (rhv.get_x() + rhv.get_y());
}

bool operator> (const Point& lhv, const Point& rhv) {
    return rhv < lhv;
}

bool operator>= (const Point& lhv, const Point& rhv) {
    return !(lhv < rhv);
}

bool operator<= (const Point& lhv, const Point& rhv) {
    return !(lhv > rhv);
}

std::ostream& operator<< (std::ostream& os, const Point& obj) {
    os << obj.get_x() << ' ' << obj.get_y();
    return os;
}

// segmentation fault
// std::istream& operator>> (std::istream& is, const Point& obj) {
//     is >> obj.m_x >> obj.m_y;
//     return is;
// }