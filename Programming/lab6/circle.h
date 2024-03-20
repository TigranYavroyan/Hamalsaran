#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <cmath>
#include "point.h"

class Circle {
public:
    Circle (double radius, double x, double y);
    Circle (double x, double y);
    Circle (double radius);
public:
    void set_radius (double radius);
    void set_x (double x);
    void set_y (double y);
    void set_point (const Point& p);
    double get_radius () const;
    double get_x () const;
    double get_y () const;
    Point get_point () const;
    std::string info () const;
private:
    class outside_X0Y : public std::exception {
    public:
        outside_X0Y (const char* msg);
        const char* what () const noexcept override; // without noexcept there is error of overriding
    };

    double m_radius;
    Point m_center;

    bool _inside_X0Y (double radius, double x, double y);
    void _error (const char* func_name);
};

namespace circle_utility {
    bool is_belong_to_circle (const Circle& c, double x, double y);
    // size_t crossing_points (const Circle& c1, const Circle& c2);
    double circles_length (const Circle& c);
    double circles_surface (const Circle& c);
    double centers_distance (const Circle& c1, const Circle& c2);
    void offset_parallel_from_OX (Circle& c, double y);
    void offset_parallel_from_OY (Circle& c, double x);
    void increase_surface (Circle& c, double k);
}

#endif // CIRCLE_H
