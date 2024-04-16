#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    Point (double x);
    Point (double x, double y);
    // seg fault
    friend std::istream& operator>> (std::istream& is, Point& obj);
public:
    void set_x (double x);
    void set_x_y (double x, double y);
    double get_x () const;
    double get_y () const;
public:
    Point& operator-- ();
    Point operator-- (int);
    Point& operator++ ();
    Point operator++ (int);
    // Point& operator+= (const Point& rhv);
private:
    double m_x;
    double m_y;
};

std::ostream& operator<< (std::ostream& os, const Point& obj);

Point operator+ (const Point& lhv, const Point& rhv);
Point operator- (const Point& lhv, const Point& rhv);
Point& operator+= (Point& lhv, const Point& rhv);
Point& operator-= (Point& lhv, const Point& rhv);
bool operator== (const Point& lhv, const Point& rhv);
bool operator!= (const Point& lhv, const Point& rhv);
bool operator< (const Point& lhv, const Point& rhv);
bool operator> (const Point& lhv, const Point& rhv);
bool operator<= (const Point& lhv, const Point& rhv);
bool operator>= (const Point& lhv, const Point& rhv);

#endif // POINT_H