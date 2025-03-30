#include <iostream>

void allocateMemory() {
    int* ptr = new int(10);
    std::cout << *ptr << std::endl;
    delete ptr; // Must manually free memory
}

int main() {
    allocateMemory();
}
