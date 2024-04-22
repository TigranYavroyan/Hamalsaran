#include "Car.h"
#include <iostream>

Car::Car (const Engine& engine, size_t sits_count, const std::string& produced_by, const std::string& model, double price, double weight, double max_speed , double date) :
    Vehicle{engine, produced_by, model, price, weight, max_speed, date},
    m_sits_count{sits_count} {}

Car::~Car () {std::cout << "Cars dtor called" << std::endl;}

void Car::set_sits_count (size_t sits_count) {
    m_sits_count = sits_count;
}

size_t Car::get_sits_count () const {
    return m_sits_count;
}

std::ostream& operator << (std::ostream& os, const Car& car) {
    os << static_cast<const Vehicle&>(car) << '\n' << car.get_sits_count();
    return os;
}


void Car::draw() const {
    std::cout << "This is the Cars::draw()" << std::endl;
}

