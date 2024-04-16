#include "Vehicle.h"

Vehicle::Vehicle (const Engine& engine, const std::string& produced_by, const std::string& model, double price, double weight, double max_speed, double date) :
    m_engine{engine},
    m_produced_by{produced_by},
    m_model(model),
    m_price{price},
    m_weight{weight},
    m_max_speed{max_speed},
    m_date{date} {}


void Vehicle::set_engine (const Engine& other) {
    m_engine = other;
}

void Vehicle::set_producer (const std::string& producer) {
    m_produced_by = producer;
}

void Vehicle::set_model (const std::string& model) {
    m_model = model;
}

void Vehicle::set_price (double price) {
    m_price = price;
}

void Vehicle::set_weight (double weight) {
    m_weight = weight;
}

void Vehicle::set_max_speed (double max_speed) {
    m_max_speed = max_speed;
}

void Vehicle::set_data (double data) {
    m_date = data;
}

Engine Vehicle::get_engine () const {
    return m_engine;
}

std::string Vehicle::get_producer () const {
    return m_produced_by;
}

std::string Vehicle::get_model () const {
    return m_model;
}

double Vehicle::get_price () const {
    return m_price;
}

double Vehicle::get_weight () const {
    return m_weight;
}

double Vehicle::get_max_speed () const {
    return m_max_speed;
}

double Vehicle::get_data () const {
    return m_date;
}