#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
public:
    Car (const Engine& engine = Engine("V6", petrol, 500, 2020), size_t sits_count = 4, const std::string& produced_by = "Gegham", 
        const std::string& model = "Mator", double price = 15000.5, double weight = 5000, double max_speed = 500, double date = 2024);
    void set_sits_count (size_t sits_count);
    size_t get_sits_count () const;
private:
    size_t m_sits_count;
};

#endif // CAR_H