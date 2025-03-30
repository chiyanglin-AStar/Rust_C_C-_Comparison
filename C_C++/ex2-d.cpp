#include <iostream>

void print(int* ptr) {
    if (ptr) {
        std::cout << *ptr << std::endl;
    } else {
        std::cout << "Pointer is null" << std::endl;
    }
}

int main() {
    int a =10;
    int* ptr = nullptr;
    //int* ptr = &a;
    print(ptr); // Potential null pointer dereference
    return 0;
}
