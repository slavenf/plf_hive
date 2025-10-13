// g++ -std=c++20 -Wall -Wextra -Wfatal-errors -DPLF_CONSTEXPR=constexpr test.cpp -o test

#include "plf_hive.h"

#include <iostream>

int main()
{
    plf::hive<int> h;

    auto it_10 = h.insert(10);
    auto it_20 = h.insert(20);
    auto it_30 = h.insert(30);
    auto it_40 = h.insert(40);

    std::cout << "size:     " << h.size() << std::endl;
    std::cout << "capacity: " << h.capacity() << std::endl;
    std::cout << "elements: ";
    for (const auto& elem : h)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
