#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 ;//= std::move(v1); // Move v1 to v2

    std::cout << "v1 size: " << v1.size() << std::endl; // v1 is now in a valid but unspecified state
    
    v2 = std::move(v1); // Move v1 to v2
    
    std::cout << "v1 size: " << v1.size() << std::endl; // v1 is now in a valid but unspecified state
    
    std::cout << "v2 size: " << v2.size() << std::endl;

    return 0;
}
