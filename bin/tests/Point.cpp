#include <GraceFt/Point.hpp>

using namespace GFt;

int main() {
    iPoint p1(1, 2);
    fPoint p2(static_cast<fPoint>(p1));
    p2 *= 2.0f;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p1: " << p2 << std::endl;
    std::cout << "p1 * p2: " << static_cast<fPoint>(p1) * p2 << std::endl;
    std::cout << "p1 + p2: " << static_cast<fPoint>(p1) + p2 << std::endl;
    std::cout << "p1 - p2: " << static_cast<fPoint>(p1) - p2 << std::endl;

    std::cout << "distance(p1, p2): " << distance(static_cast<fPoint>(p1), p2) << std::endl;
    std::cout << "norm(p1): " << p1.norm() << std::endl;
    std::cout << "norm(p2): " << p2.norm() << std::endl;

    fPoint p3(0.1f, 0.2f);
    fPoint p4(0.2f, 0.1f);
    fPoint p5(0.3f, 0.3f);

    std::cout << "p3: " << p3 << std::endl;
    std::cout << "p4: " << p4 << std::endl;
    std::cout << "p5: " << p5 << std::endl;
    std::cout << "p3 + p4: " << p3 + p4 << std::endl;
    std::cout << "safe float: " << (p3 + p4 == p5) << std::endl;

    std::cout << (0.1 + 0.2 == 0.3) << std::endl;

    return 0;
}