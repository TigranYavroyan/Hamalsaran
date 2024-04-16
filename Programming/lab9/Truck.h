#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
public:
    Truck (const Engine& engine = Engine("V6", petrol, 500, 2020), const std::string& produced_by = "Gegham", 
        const std::string& model = "Mator", double price = 15000.5, double weight = 5000, double max_speed = 500, double date = 2024,  double lifting_capacity = 20000);
    void set_lifting_capacity (double lifting_capacity);
    double get_lifting_capacity () const;
private:
    double m_lifting_capacity;
};

#endif // TRUCK_H