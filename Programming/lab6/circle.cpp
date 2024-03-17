#include "circle.h"
#include <cstring>

void Circle::_error (const char* func_name) {
    std::string msg = "Input is not correct in " + std::string(func_name) + "\n";
    throw outside_X0Y(msg.data());
}

bool Circle::_inside_X0Y (double radius, double x, double y) {
    return !(radius < 0 || radius > x || radius > y);
}

Circle::outside_X0Y::outside_X0Y (const char* msg) : message(msg) {
    std::cerr << msg;
}

const char* Circle::outside_X0Y::what () {
    return message;
}

Circle::Circle (double radius, double x, double y) {
    if (!_inside_X0Y(radius, x, y))
        _error(__func__);
    m_radius = radius;
    m_x = x;
    m_y = y;
}

Circle::Circle (double x, double y) : Circle ((x < y ? x : y), x, y) {}

Circle::Circle (double radius) : Circle (radius, radius, radius) {}

void Circle::set_radius (double radius) {
    if (!_inside_X0Y(radius, m_x, m_y))
        _error(__func__);
    m_radius = radius;
}

void Circle::set_x (double x) {
    if (x < m_radius)
        _error(__func__);
    m_x = x;
}

void Circle::set_y (double y) {
    if (y < m_radius)
        _error(__func__);
    m_y = y;
}

double Circle::get_x () const {
    return m_x;
}

double Circle::get_y () const {
    return m_y;
}

double Circle::get_radius () const {
    return m_radius;
}

std::string Circle::info () const {
    using std::to_string;
    return "R: " + to_string(m_radius) + "\nX: " + to_string(m_x) + "\nY: " + to_string(m_y);
}

bool is_belong_to_circle (const Circle& c, double x, double y) {
    return (sqrt(pow(x - c.get_x(), 2) + pow(y - c.get_y(), 2)) <= c.get_radius());
}

double circles_length (const Circle& c) {
    return 2 * M_PI * c.get_radius();
}

double circles_surface (const Circle& c) {
    return M_PI * c.get_radius() * c.get_radius();
}

double centers_distance (const Circle& c1, const Circle& c2) {
    return sqrt(pow(c2.get_x() - c1.get_x(), 2) + pow(c2.get_y() - c1.get_y(), 2));
}

void offset_parallel_from_OX (Circle& c, double y) {
    c.set_y(c.get_y() + y);
}

void offset_parallel_from_OY (Circle& c, double x) {
    c.set_x(c.get_x() + x);
}

void increase_surface (Circle& c, double k) {
    c.set_radius(c.get_radius() * sqrt(k));
}