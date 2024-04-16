#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <cmath>
#include "point.h"

class Circle;

namespace circle_utility {
    bool is_belong_to_circle (const Circle& c, double x, double y);
    double circles_surface (const Circle& c);
    double circles_length (const Circle& c);
    double centers_distance (const Circle& c1, const Circle& c2);
    void offset_parallel_from_OX (Circle& c, double y);
    void offset_parallel_from_OY (Circle& c, double x);
    void increase_surface (Circle& c, double k);
}

class Circle {
public:
    friend double circle_utility::circles_surface (const Circle& c);
    // // segmentation fault
    // friend std::istream& operator>> (std::istream& is, const Point& obj);

    Circle (double radius, double x, double y);
    Circle (double x, double y);
    Circle (double radius);
    Circle (const Circle& other);
    ~Circle ();
public:
    Circle& set_radius (double radius);
    Circle& set_x (double x);
    Circle& set_y (double y);
    Circle& set_point (const Point& p);
    double get_radius () const;
    double get_x () const;
    double get_y () const;
    Point get_point () const;
    std::string info () const;
    static size_t get_count ();
public:
    Circle& operator= (const Circle& rhv);
private:
    class outside_X0Y : public std::exception {
    public:
        outside_X0Y (const char* msg);
        const char* what () const noexcept override;
    };

    double m_radius;
    Point* m_center;
    static size_t s_count;

    bool _inside_X0Y (double radius, double x, double y);
    void _error (const char* func_name);
};

std::ostream& operator<< (std::ostream& os, const Circle& obj);

#endif // CIRCLE_H
