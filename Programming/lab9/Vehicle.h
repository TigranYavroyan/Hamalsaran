#ifndef VEHICLE_H
#define VEHICLE_H

#include "Engine.h"

class Vehicle {
public:
    Vehicle (const Engine& engine = Engine("V6", petrol, 500, 2020), const std::string& produced_by = "Gegham", 
                const std::string& model = "Mator", double price = 15000.5, double weight = 5000, double max_speed = 500, double date = 2024);
    virtual ~Vehicle ();
    void set_engine (const Engine& other);
    void set_producer (const std::string& producer);
    void set_model (const std::string& model);
    void set_price (double price);
    void set_weight (double weight);
    void set_max_speed (double max_speed);
    void set_data (double data);
    Engine get_engine () const;
    std::string get_producer () const;
    std::string get_model () const;
    double get_price () const;
    double get_weight () const;
    double get_max_speed () const;
    double get_data () const;
    
    virtual void draw () const;
private:
    Engine m_engine;
    std::string m_produced_by;
    std::string m_model;
    double m_price;
    double m_weight;
    double m_max_speed;
    double m_date;
};

std::ostream& operator << (std::ostream& os, const Vehicle& vehicle);
#endif // VEHICLE_H