// g++ -std=c++20 -Wall -Wextra -Wfatal-errors -DPLF_CONSTEXPR=constexpr test.cpp -o test

#include "plf_hive.h"

#include <iostream>

int main()
{
    plf::hive<int> h;

    auto it_10 = h.insert(10);

    std::cout << "size:     " << h.size() << std::endl;
    std::cout << "capacity: " << h.capacity() << std::endl;
    std::cout << "elements: ";
    for (const auto& elem : h)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
