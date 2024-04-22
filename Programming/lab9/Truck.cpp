#include "Truck.h"
#include <iostream>

Truck::Truck (const Engine& engine, const std::string& produced_by, const std::string& model, double price, double weight, double max_speed , double date, double lifting_capacity) :
    Vehicle{engine, produced_by, model, price, weight, max_speed, date},
    m_lifting_capacity{lifting_capacity} {}

Truck::~Truck () {std::cout << "Trucks dtor called" << std::endl;}

void Truck::set_lifting_capacity (double lifting_capacity) {
    m_lifting_capacity = lifting_capacity;
}

double Truck::get_lifting_capacity () const {
    return m_lifting_capacity;
}

std::ostream& operator << (std::ostream& os, const Truck& truck) {
    os << static_cast<const Truck&>(truck) << '\n' << truck.get_lifting_capacity();
    return os;
}

void Truck::draw() const {
    std::cout << "This is the Trucks::draw()" << std::endl;
}