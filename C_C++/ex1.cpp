#include <iostream>

int main() {
    int* ptr = new int(10); // Allocate memory
    std::cout << *ptr << std::endl;
    delete ptr; // Manually free memory
    // ptr is now a dangling pointer
    return 0;
}