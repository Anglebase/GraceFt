#include <Point.hpp>

using namespace GFt;

int main() {
    iPoint p1(1, 2);
    fPoint p2(cast<float>(p1));
    p2 *= 2.0f;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p1: " << p2 << std::endl;
    std::cout << "p1 * p2: " << cast<float>(p1) * p2 << std::endl;
    std::cout << "p1 + p2: " << cast<float>(p1) + p2 << std::endl;
    std::cout << "p1 - p2: " << cast<float>(p1) - p2 << std::endl;

    std::cout << "distance(p1, p2): " << distance(cast<float>(p1), p2) << std::endl;
    std::cout << "norm(p1): " << p1.norm() << std::endl;
    std::cout << "norm(p2): " << p2.norm() << std::endl;
    
    return 0;
}