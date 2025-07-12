/*5. Create a base class Vehicle with attributes for make and model. Derive 
a class Car that adds an attribute for the number of doors. Include 
appropriate constructors and a function to display details.*/

#include <iostream>
#include <string>

class Vehicle {
protected:
    std::string make;
    std::string model;

public:
    Vehicle(const std::string& mk, const std::string& mdl)
        : make(mk), model(mdl) {}

    void displayDetails() const {
        std::cout << "Make: " << make << std::endl;
        std::cout << "Model: " << model << std::endl;
    }
};

class Car : public Vehicle {
private:
    int numberOfDoors;

public:
    Car(const std::string& mk, const std::string& mdl, int doors)
        : Vehicle(mk, mdl), numberOfDoors(doors) {}

    void displayDetails() const {
        Vehicle::displayDetails();
        std::cout << "Number of Doors: " << numberOfDoors << std::endl;
    }
};

int main() {
    Car myCar("Toyota", "Corolla", 4);

    std::cout << "Car Details:" << std::endl;
    myCar.displayDetails();

    return 0;
}
