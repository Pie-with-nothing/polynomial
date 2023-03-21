#include "polychlen.hpp"
#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    // double d = 8.123456789012345;
    // float f = 8.999999;
    // double dd = f;

    // std::cout << std::fixed << d;
    float *a = new float[4]{1, 2, 3, 4};
    Poly p(a, 4);
    std::cout << p << "\n";
    Poly in{1., 2., 3.909, 3.4444};
    Poly cp = -in;
    std::cout << static_cast<std::string>(cp) << "\n";
    std::cout << p * p << "\n";
    Poly one{1.};
    std::cout << one.degree() << "\n";
    std::cout << ((p * p / p) == p) << "\n";
    delete[] a;
    return 0;
}
