#include <iostream>

class Animal {
public:
    virtual void speak() const = 0;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};

int main() {
    Animal* animal = new Dog();
    animal->speak();
    delete animal;
    return 0;
}
