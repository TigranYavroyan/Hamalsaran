#include "Polynom.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

int Polynom::s_obj_count = 0;

Polynom::Polynom () : m_coefficients(size, 0), m_degrees(size, 0), m_variable('x') { ++s_obj_count; }

Polynom::Polynom (const std::vector<double>& coefficients) : 
    m_coefficients(size, 0), 
    m_degrees(size, 1), 
    m_variable('x')
{
    ++s_obj_count;
    set_coefficients(coefficients);
}

Polynom::Polynom (const std::vector<int>& degrees) :
    m_coefficients(size, 1), 
    m_degrees(size, 0), 
    m_variable('x')
{
    ++s_obj_count;
    set_degrees(degrees);
}

Polynom::Polynom (const std::vector<double>& coefficients, const std::vector<int>& degrees, char variable) :
    m_coefficients(size, 0), 
    m_degrees(size, 0), 
    m_variable('x')
{
    ++s_obj_count;
    set_all(coefficients, degrees, variable);
}

Polynom::~Polynom () {
    --s_obj_count;
}

void Polynom::set_coefficients (const std::vector<double>& coefficients) {
    if (coefficients.size() != size)
        throw std::out_of_range("");
    m_coefficients = coefficients;
}

void Polynom::set_degrees (const std::vector<int>& degrees) {
    if (degrees.size() != size)
        throw std::out_of_range("");
    m_degrees = degrees;
}

void Polynom::set_all (const std::vector<double>& coefficients, const std::vector<int>& degrees, char variable) {
    set_coefficients(coefficients);
    set_degrees(degrees);
    m_variable = variable;
}

std::vector<double> Polynom::get_coefficients () const {
    return m_coefficients;
}

std::vector<int> Polynom::get_degrees () const {
    return m_degrees;
}

char Polynom::get_variable () const {
    return m_variable;
}

static inline double ft_abs (double op) {
    return (op < 0) ? -op : op;
}

static std::string minimize(int num) {
    static const std::string superscripts[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};
    std::string result;
    while (num > 0) {
        result = superscripts[num % 10] + result;
        num /= 10;
    }
    return result;
}

int Polynom::get_obj_count () {
    return s_obj_count;
}

void Polynom::display () const {
    char input = '+';
    for (int i = 0; i < size; ++i) {
        if (m_coefficients[i] != 0) {
            (m_coefficients[i] < 0) ? input = '-' : input = '+';
            if (i != 0)
                std::cout << ' ' << input << ' ';
            std::cout << ft_abs(m_coefficients[i]);
            if (m_degrees[i] == 1)
                std::cout << m_variable;
            else if (m_degrees[i] != 0)
                std::cout << m_variable << minimize(m_degrees[i]);
                // std::cout << m_variable << '^' << m_degrees[i]; // my display logic
        }
    }
    std::cout << std::endl;
}

Polynom calcDerivative (const Polynom& pol, int degree) {
    std::vector<int> res_degrees = pol.get_degrees();
    std::vector<double> res_coefficients = pol.get_coefficients();
    char res_variable = pol.get_variable();
    for (int i = 0; i < degree; ++i) {
        for (int j = 0; j < size; ++j) {
            res_coefficients[j] *= res_degrees[j];
            --res_degrees[j];
        }
    }
    return Polynom(res_coefficients, res_degrees, res_variable);
}

double calcPolynom(const Polynom& pol, double x) {
    double res = 0;
    std::vector<double> coeffs = pol.get_coefficients();
    std::vector<int> degr = pol.get_degrees();
    for (int i = 0; i < size; ++i) {
        res += coeffs[i] * pow(x, degr[i]);
    }
    return res;
}