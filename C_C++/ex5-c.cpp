#include <iostream>

int* getPointer(bool valid) {
    if (valid) return new int(10);
    return nullptr; // Unsafe: null pointer possibility
}

int main() {
    int* ptr = getPointer(false);
    std::cout << *ptr << std::endl; // Segmentation fault
}
