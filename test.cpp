// g++ -std=c++20 -Wall -Wextra -Wfatal-errors -DPLF_CONSTEXPR=constexpr test.cpp -o test

#include <iostream>

#include "plf_hive.h"

int main()
{
    plf::hive<int> h(plf::hive_limits(4, 128));

    auto it_10 = h.insert(10);
    auto it_20 = h.insert(20);
    auto it_30 = h.insert(30);
    auto it_40 = h.insert(40);
    // auto it_50 = h.insert(50);
    // auto it_60 = h.insert(60);
    // auto it_70 = h.insert(70);
    // auto it_80 = h.insert(80);

    std::cout << "size:     " << h.size() << std::endl;
    std::cout << "capacity: " << h.capacity() << std::endl;
    std::cout << "elements: ";
    for (const auto& elem : h)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    h.erase(it_10);
    h.erase(it_20);
    h.erase(it_30);
    h.erase(it_40);

    std::cout << "size:     " << h.size() << std::endl;
    std::cout << "capacity: " << h.capacity() << std::endl;
    std::cout << "elements: ";
    for (const auto& elem : h)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    h.insert(11);
    h.insert(21);
    h.insert(31);
    h.insert(41);
    h.insert(90);

    std::cout << "size:     " << h.size() << std::endl;
    std::cout << "capacity: " << h.capacity() << std::endl;
    std::cout << "elements: ";
    for (const auto& elem : h)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
