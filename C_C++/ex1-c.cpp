#include <iostream>
using namespace std;

int* getPointer() {
    int x = 10;
    return &x; // Returning a pointer to a local variable (undefined behavior)
}

int main() {
    int* p = getPointer();
    cout << *p << endl; // Undefined behavior: accessing a dangling pointer
}
