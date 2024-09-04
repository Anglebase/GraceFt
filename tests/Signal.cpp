#include <Signal.hpp>
#include <iostream>
#include <string>

using namespace GFt;
using namespace std;

int main() {
    Signal<int> sig;
    sig.connect([](int i) { std::cout << "Hello, World!" << std::endl; });
    sig.emit(1);

    Signal<int, float> sig2;
    sig2.connect([](int i, float f) { std::cout << "i: " << i << ", f: " << f << std::endl; });
    auto id = sig2.connect([](int i, float f) { std::cout << "i: " << i << ", f: " << f << std::endl; });
    sig2.emit(2, 3.0f);
    sig2.disconnect(id);
    sig2.emit(4, 5.0f);

    Signal<std::string> sig3;
    sig3.connect([](const std::string& s) { std::cout << "s: " << s << std::endl; });
    sig3.emit("Hello, Signal!");

    Signal sig4;
    sig4.connect([]() { std::cout << "Empty signal!" << std::endl; });
    sig4.emit();
    auto id2 = sig4.connect([]() { std::cout << "Another empty signal!" << std::endl; });
    sig4.emit();
    sig4.disconnect(id2);
    sig4.emit();
    return 0;
}