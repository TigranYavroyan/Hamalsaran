#include <iostream>
#include "Car.h"

#include <vector>

template <int N>
void print_by_decreasing (Car (&cars)[N]) {
    std::vector<Car> my_cars;
    for (int i = 0; i < N; ++i) {
        if (cars[i].get_sits_count() < 6)
            my_cars.push_back(cars[i]);
    }
    std::sort(my_cars.begin(), my_cars.end(), [](const Car& car1, const Car& car2) 
    {
        return car1.get_engine().get_power() > car2.get_engine().get_power();
    });
    for (auto i : my_cars) {
        std::cout << i.get_engine().get_name() << " -> " << i.get_engine().get_power() << std::endl;
    }
}

int main () {
    Car cars[5] = {
        Car(Engine("V6", petrol, 8000, 2024), 6),
        Car(Engine("V7", petrol, 7000, 2024), 4),
        Car(Engine("V8", petrol, 9000, 2024), 4),
        Car(Engine("V9", petrol, 6000, 2024), 4),
        Car(Engine("V10", petrol, 5000, 2024), 7)
    };
    print_by_decreasing(cars);
}