#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();
        ++shared_data;
        mtx.unlock();
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
