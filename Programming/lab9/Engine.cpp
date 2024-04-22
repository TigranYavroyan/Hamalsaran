#include "Engine.h"
#include <iostream>

Engine::Engine (const std::string& name, Engine_type engine_type, double power, int date) :
    m_name{name},
    m_engine_type{engine_type},
    m_power{power},
    m_date{date} {}

void Engine::set_name (const std::string& name) {
    m_name = name;
}

void Engine::set_engine_type (Engine_type engine_type) {
    m_engine_type = engine_type;
}

void Engine::set_power (double power) {
    m_power = power;
}

void Engine::set_date (int date) {
    m_date = date;
}

std::string Engine::get_name () const {
    return m_name;
}

Engine_type Engine::get_engine_type () const {
    return m_engine_type;
}

double Engine::get_power () const {
    return m_power;
}

int Engine::get_date () const {
    return m_date;
}

static std::ostream& operator << (std::ostream& os, Engine_type engine_type) {
    switch (engine_type)
    {
        case diesel:
            os << "diesel";
            break;
        case petrol:
            os << "petrol";
            break;
        case gas:
            os << "gas";
            break;
        case electric:
            os << "electric";
            break;
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const Engine& engine) {
    os << "name -> " << engine.get_name() << "\nengine_type -> " 
        << engine.get_engine_type() << "\npower -> " << engine.get_power() 
        << "\ndate -> " << engine.get_date();
    return os;
}

Engine::~Engine () = default;