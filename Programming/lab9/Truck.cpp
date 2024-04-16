#include "Truck.h"

Truck::Truck (const Engine& engine, const std::string& produced_by, const std::string& model, double price, double weight, double max_speed , double date, double lifting_capacity) :
    Vehicle{engine, produced_by, model, price, weight, max_speed, date},
    m_lifting_capacity{lifting_capacity} {}

void Truck::set_lifting_capacity (double lifting_capacity) {
    m_lifting_capacity = lifting_capacity;
}

double Truck::get_lifting_capacity () const {
    return m_lifting_capacity;
}