#include <iostream>

bool divide(int a, int b, int& result) {
    if (b == 0) {
        return false; // Error
    }
    result = a / b;
    return true; // Success
}

int main() {
    int result;
    if (!divide(10, 0, result)) {
        std::cout << "Division by zero!" << std::endl;
    } else {
        std::cout << "Result: " << result << std::endl;
    }
    return 0;
}
