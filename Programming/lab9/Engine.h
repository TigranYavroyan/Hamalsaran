#ifndef ENGINE_H
#define ENGINE_H

#include <string>

enum Engine_type {diesel, petrol, gas, electric};

class Engine {
public:
    Engine (const std::string& name = "Mi ban", Engine_type engine_type = gas, double power = 500, int date = 2024);
    void set_name (const std::string& name);
    void set_engine_type (Engine_type engine_type);
    void set_power (double power);
    void set_date (int date);
    std::string get_name () const;
    Engine_type get_engine_type () const;
    double get_power () const;
    int get_date () const;
    ~Engine ();
private:
    std::string m_name;
    Engine_type m_engine_type;
    double m_power;
    int m_date;
};

std::ostream& operator << (std::ostream& os, const Engine& engine);

#endif // ENGINE_H