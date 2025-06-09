#include <GraceFt/Channel.hpp>
#include <thread>
#include <iostream>

using namespace GFt;
using namespace std::chrono_literals;
using namespace std;

Channel<int> channel;

void f1() {
    for (int i = 0; i < 10; i++) {
        std::cout << "f1 sending " << i << std::endl;
        channel.send(i);
        std::this_thread::sleep_for(100ms);
    }
}
void f2() {
    for (int i = 0; i < 10; i++) {
        std::cout << "f2 receiving " << std::endl;
        std::cout << channel.recv() << std::endl;
    }
}

int main() {
    std::thread t1(f1);
    std::thread t2(f2);
    t1.join();
    t2.join();
    return 0;
}