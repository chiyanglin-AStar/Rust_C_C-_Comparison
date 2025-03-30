#include <iostream>

void printNumber(double num) {
    std::cout << num << std::endl;
}

int main() {
    printNumber(10); // Implicitly converts int to double
}
