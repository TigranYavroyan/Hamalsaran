#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <stddef.h>

const size_t size = 6;

class Polynom {
public:
    Polynom (); // all 0
    Polynom (const std::vector<double>& coefficients); // degrees = 1
    Polynom (const std::vector<int>& degrees); // coefficients = 1
    Polynom (const std::vector<double>& coefficients, const std::vector<int>& degrees, char variable);
    ~Polynom ();
public:
    void set_coefficients (const std::vector<double>& coefficients);
    void set_degrees (const std::vector<int>& degrees);
    void set_all (const std::vector<double>& coefficients, const std::vector<int>& degrees, char variable);
    std::vector<double> get_coefficients () const;
    std::vector<int> get_degrees () const;
    char get_variable () const;
    static int get_obj_count ();
    void display () const;
private:
    std::vector<double> m_coefficients;
    std::vector<int> m_degrees;
    char m_variable;
    
    static int s_obj_count;
};

#include "Polynom.cpp"

#endif // POLYNOM_H