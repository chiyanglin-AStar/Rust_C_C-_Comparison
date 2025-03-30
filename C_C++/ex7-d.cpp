#include <iostream>

#define SQUARE(x) ((x) * (x))

int main() {
    int x = 5;
    std::cout << SQUARE(x + 1) << std::endl; // Outputs 11, not 36
    return 0;
}
