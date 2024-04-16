#include "Car.h"

Car::Car (const Engine& engine, size_t sits_count, const std::string& produced_by, const std::string& model, double price, double weight, double max_speed , double date) :
    Vehicle{engine, produced_by, model, price, weight, max_speed, date},
    m_sits_count{sits_count} {}

void Car::set_sits_count (size_t sits_count) {
    m_sits_count = sits_count;
}

size_t Car::get_sits_count () const {
    return m_sits_count;
}