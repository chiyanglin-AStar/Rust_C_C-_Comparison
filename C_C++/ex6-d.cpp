#include <iostream>
//int x =10;
int* create_int() {
    int x = 10;
    return &x; // Dangling reference
}

int main() {
    int* ptr = create_int();
    std::cout << *ptr << std::endl; // Undefined behavior
    return 0;
}
