#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle (const Engine& engine, const std::string& produced_by, const std::string& model, double price, double weight, double max_speed, double date) :
    m_engine{engine},
    m_produced_by{produced_by},
    m_model(model),
    m_price{price},
    m_weight{weight},
    m_max_speed{max_speed},
    m_date{date} {}

Vehicle::~Vehicle () {std::cout << "Vehicles dtor called" << std::endl;}


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

std::ostream& operator << (std::ostream& os, const Vehicle& vehicle) {
    os << vehicle.get_engine() << '\n' << vehicle.get_producer() << '\n' << vehicle.get_model() << '\n' 
        << vehicle.get_price() << '\n' << vehicle.get_weight() << '\n'
        << vehicle.get_max_speed() << '\n' << vehicle.get_data();
    return os;
}

void Vehicle::draw() const {
    std::cout << "This is the Vehicles::draw()" << std::endl;
}