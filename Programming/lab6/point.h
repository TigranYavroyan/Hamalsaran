#ifndef POINT_H
#define POINT_H

class Point {
public:
    explicit Point (double x);
    Point (double x, double y);
public:
    void set_x (double x);
    void set_x_y (double x, double y);
    double get_x () const;
    double get_y () const;
private:
    double m_x;
    double m_y;
};

#endif // POINT_H