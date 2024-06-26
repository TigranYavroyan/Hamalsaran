#include "circle.h"
#include <cstring>

size_t Circle::s_count = 0;

size_t Circle::get_count() {
    return s_count;
}

void Circle::_error (const char* func_name) {
    std::string msg = "Input is not correct in " + std::string(func_name) + "\n";
    throw outside_X0Y(msg.data());
}

bool Circle::_inside_X0Y (double radius, double x, double y) {
    return !(radius < 0 || radius > x || radius > y);
}

Circle::outside_X0Y::outside_X0Y (const char* msg) {
    std::cerr << msg;
}

const char* Circle::outside_X0Y::what () const noexcept {
    return "outside of X0Y";
}

Circle::Circle (double radius, double x, double y) {
    if (!_inside_X0Y(radius, x, y))
        _error(__func__);
    m_radius = radius;
    m_center = new Point(x, y);
    ++s_count;
}

Circle::Circle (double x, double y) : Circle ((x < y ? x : y), x, y) {}

Circle::Circle (double radius) : Circle (radius, radius, radius) {}

Circle& Circle::set_radius (double radius) {
    if (!_inside_X0Y(radius, m_center->get_x(), m_center->get_y()))
        _error(__func__);
    m_radius = radius;
    return *this;
}

Circle::Circle (const Circle& other) : m_center(new Point(other.get_x(), other.get_y())), m_radius(other.m_radius) {}

Circle& Circle::operator= (const Circle& rhv) {
    if (this == &rhv)
        return *this;
    delete m_center;
    m_center = new Point(rhv.get_x(), rhv.get_y());
    m_radius = rhv.m_radius;
    return *this;
}

Circle::~Circle () { --s_count; delete m_center; }

Circle& Circle::set_x (double x) {
    if (x < m_radius)
        _error(__func__);
    m_center->set_x(x);
    return *this;
}

Circle& Circle::set_y (double y) {
    if (y < m_radius)
        _error(__func__);
    m_center->set_x_y(m_center->get_x(), y);
    return *this;
}

Circle& Circle::set_point (const Point& p) {
    if (!_inside_X0Y(m_radius, p.get_x(), p.get_y()))
        _error(__func__);
    *m_center = p;
    return *this;
}

double Circle::get_x () const {
    return m_center->get_x();
}

double Circle::get_y () const {
    return m_center->get_y();
}

double Circle::get_radius () const {
    return m_radius;
}

Point Circle::get_point () const {
    return *m_center;
}

std::string Circle::info () const {
    using std::to_string;
    return "R: " + to_string(m_radius) + "\nX: " + to_string(m_center->get_x()) + "\nY: " + to_string(m_center->get_y());
}

bool circle_utility::is_belong_to_circle (const Circle& c, double x, double y) {
    return (sqrt(pow(x - c.get_x(), 2) + pow(y - c.get_y(), 2)) <= c.get_radius());
}

double circle_utility::circles_length (const Circle& c) {
    return 2 * M_PI * c.get_radius();
}

double circle_utility::circles_surface (const Circle& c) { // Circles friend
    return M_PI * c.get_radius() * c.get_radius();
}

double circle_utility::centers_distance (const Circle& c1, const Circle& c2) {
    return sqrt(pow(c2.get_x() - c1.get_x(), 2) + pow(c2.get_y() - c1.get_y(), 2));
}

void circle_utility::offset_parallel_from_OX (Circle& c, double y) {
    c.set_y(c.get_y() + y);
}

void circle_utility::offset_parallel_from_OY (Circle& c, double x) {
    c.set_x(c.get_x() + x);
}

void circle_utility::increase_surface (Circle& c, double k) {
    c.set_radius(c.get_radius() * sqrt(k));
}

std::ostream& operator<< (std::ostream& os, const Circle& obj) {
    os << obj.info();
    return os;
}

// // segmentation fault
// std::istream& operator>> (std::istream& is, const Point& obj) {
//     is >> obj.m_x >> obj.m_y;
//     return is;
// }