// g++ -std=c++20 -Wall -Wextra -Wfatal-errors -DPLF_CONSTEXPR=constexpr test.cpp -o test

#include <cassert>
#include <iostream>

#include "plf_hive.h"

template <typename Container, typename Size>
typename Container::const_iterator nth(const Container& c, Size pos)
{
    typename Container::const_iterator it = c.cbegin();

    for (Size i = 0; i < pos; ++i)
    {
        ++it;
    }

    return it;
}

int main()
{
    // Test insert into newly created container
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        const std::vector<int> elements({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200});

        for (int i = 0; i < int(elements.size()); ++i)
        {
            const auto& elem = elements[i];

            std::cout << "Inserting element " << elem << std::endl;

            h.insert(elem);

            assert(int(h.size()) == i + 1);

            if (h.size() <= 4)
            {
                assert(h.capacity() == 4);
            }
            else if (h.size() <= 8)
            {
                assert(h.capacity() == 8);
            }
            else if (h.size() <= 16)
            {
                assert(h.capacity() == 16);
            }
            else
            {
                assert(h.capacity() == 32);
            }

            for (int j = 0; j < i; ++j)
            {
                assert(*nth(h, j) == *nth(elements, j));
            }
        }
    }

    // Test erase at single position (single group in container)
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        h.insert(10);
        h.insert(20);
        h.insert(30);
        h.insert(40);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10);
        assert(*nth(h, 1) == 20);
        assert(*nth(h, 2) == 30);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 0..." << std::endl;

        h.erase(nth(h, 0));

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 20);
        assert(*nth(h, 1) == 30);
        assert(*nth(h, 2) == 40);

        std::cout << "Insert one element..." << std::endl;

        h.insert(11);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 20);
        assert(*nth(h, 2) == 30);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 1..." << std::endl;

        h.erase(nth(h, 1));

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 30);
        assert(*nth(h, 2) == 40);

        std::cout << "Insert one element..." << std::endl;

        h.insert(21);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 30);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 2..." << std::endl;

        h.erase(nth(h, 2));

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 40);

        std::cout << "Insert one element..." << std::endl;

        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 31);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 3..." << std::endl;

        h.erase(nth(h, 3));

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 31);

        std::cout << "Insert one element..." << std::endl;

        h.insert(41);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 31);
        assert(*nth(h, 3) == 41);
    }

    // Test erase at positions 0, 1 and 2 (single group in container)
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10);
        assert(*nth(h, 1) == 20);
        assert(*nth(h, 2) == 30);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 0, 1 and 2..." << std::endl;

        h.erase(it0);
        h.erase(it1);
        h.erase(it2);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 31);
        assert(*nth(h, 3) == 40);
    }

    // Test erase at positions 2, 1 and 0 (single group in container)
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10);
        assert(*nth(h, 1) == 20);
        assert(*nth(h, 2) == 30);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 2, 1 and 0..." << std::endl;

        h.erase(it2);
        h.erase(it1);
        h.erase(it0);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 31);
        assert(*nth(h, 3) == 40);
    }

    // Test erase at positions 0, 2 and 1 (single group in container)
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10);
        assert(*nth(h, 1) == 20);
        assert(*nth(h, 2) == 30);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 0, 2 and 1..." << std::endl;

        h.erase(it0);
        h.erase(it2);
        h.erase(it1);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 31);
        assert(*nth(h, 3) == 40);
    }

    // Test erase at positions 2, 0 and 1 (single group in container)
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10);
        assert(*nth(h, 1) == 20);
        assert(*nth(h, 2) == 30);
        assert(*nth(h, 3) == 40);

        std::cout << "Erase at position 2, 0 and 1..." << std::endl;

        h.erase(it2);
        h.erase(it0);
        h.erase(it1);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11);
        assert(*nth(h, 1) == 21);
        assert(*nth(h, 2) == 31);
        assert(*nth(h, 3) == 40);
    }
}
