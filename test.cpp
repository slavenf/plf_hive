// g++ -std=c++20 -Wall -Wextra -Wfatal-errors -DPLF_CONSTEXPR=constexpr test.cpp -o test

#include <cassert>
#include <iostream>

#include "plf_hive.h"

template <typename Container, typename Size>
auto nth(const Container& c, Size pos)
{
    #if 1

    return std::next(c.begin(), pos);

    #else

    auto it = c.begin();

    for (Size i = 0; i < pos; ++i)
    {
        ++it;
    }

    return it;

    #endif
}

template <typename Container, typename Size>
auto rnth(const Container& c, Size pos)
{
    #if 1

    return std::next(c.rbegin(), pos);

    #else

    auto it = c.rbegin();

    for (Size i = 0; i < pos; ++i)
    {
        ++it;
    }

    return it;

    #endif
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

            #if 0 // TODO: Check hive_iterator::distance and hive_reverse_iterator::distance
            for (int j = 0; j < int(h.size()); ++j)
            {
                assert(std::distance(nth(h, j), h.cend()) == int(h.size()) - j);
                assert(std::distance(rnth(h, j), h.crend()) == int(h.size()) - j);
            }
            #endif
        }
    }

    // Test erase at single position in the same group
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10); assert(*rnth(h, 3) == 10);
        assert(*nth(h, 1) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 0..." << std::endl;

        h.erase(it0);

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 1) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 2) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Insert one element..." << std::endl;

        h.insert(11);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 1..." << std::endl;

        h.erase(it1);

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 2) == 11);
        assert(*nth(h, 1) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 2) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Insert one element..." << std::endl;

        h.insert(21);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 2) == 21);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 2..." << std::endl;

        h.erase(it2);

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 2) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 1) == 21);
        assert(*nth(h, 2) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Insert one element..." << std::endl;

        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 2) == 21);
        assert(*nth(h, 2) == 31); assert(*rnth(h, 1) == 31);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 3..." << std::endl;

        h.erase(it3);

        assert(h.size() == 3);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 2) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 1) == 21);
        assert(*nth(h, 2) == 31); assert(*rnth(h, 0) == 31);

        std::cout << "Insert one element..." << std::endl;

        h.insert(41);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 2) == 21);
        assert(*nth(h, 2) == 31); assert(*rnth(h, 1) == 31);
        assert(*nth(h, 3) == 41); assert(*rnth(h, 0) == 41);
    }

    // Test erase at positions 0, 1 and 2 in the same group
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10); assert(*rnth(h, 3) == 10);
        assert(*nth(h, 1) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 0, 1 and 2..." << std::endl;

        h.erase(it0);
        h.erase(it1);
        h.erase(it2);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 2) == 21);
        assert(*nth(h, 2) == 31); assert(*rnth(h, 1) == 31);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);
    }

    // Test erase at positions 2, 1 and 0 in the same group
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10); assert(*rnth(h, 3) == 10);
        assert(*nth(h, 1) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 2, 1 and 0..." << std::endl;

        h.erase(it2);
        h.erase(it1);
        h.erase(it0);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 2) == 21);
        assert(*nth(h, 2) == 31); assert(*rnth(h, 1) == 31);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);
    }

    // Test erase at positions 0, 2 and 1 in the same group
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10); assert(*rnth(h, 3) == 10);
        assert(*nth(h, 1) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 0, 2 and 1..." << std::endl;

        h.erase(it0);
        h.erase(it2);
        h.erase(it1);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 2) == 21);
        assert(*nth(h, 2) == 31); assert(*rnth(h, 1) == 31);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);
    }

    // Test erase at positions 2, 0 and 1 in the same group
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10); (void)it0;
        auto it1 = h.insert(20); (void)it1;
        auto it2 = h.insert(30); (void)it2;
        auto it3 = h.insert(40); (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10); assert(*rnth(h, 3) == 10);
        assert(*nth(h, 1) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 2, 0 and 1..." << std::endl;

        h.erase(it2);
        h.erase(it0);
        h.erase(it1);

        assert(h.size() == 1);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Insert three elements..." << std::endl;

        h.insert(11);
        h.insert(21);
        h.insert(31);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 11); assert(*rnth(h, 3) == 11);
        assert(*nth(h, 1) == 21); assert(*rnth(h, 2) == 21);
        assert(*nth(h, 2) == 31); assert(*rnth(h, 1) == 31);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);
    }

    // Test erase at two positions in different groups
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10);    (void)it0;
        auto it1 = h.insert(20);    (void)it1;
        auto it2 = h.insert(30);    (void)it2;
        auto it3 = h.insert(40);    (void)it3;
        auto it4 = h.insert(50);    (void)it4;
        auto it5 = h.insert(60);    (void)it5;
        auto it6 = h.insert(70);    (void)it6;
        auto it7 = h.insert(80);    (void)it7;
        auto it8 = h.insert(90);    (void)it8;
        auto it9 = h.insert(100);   (void)it9;

        assert(h.size() == 10);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);  assert(*rnth(h, 9) == 10);
        assert(*nth(h, 1) == 20);  assert(*rnth(h, 8) == 20);
        assert(*nth(h, 2) == 30);  assert(*rnth(h, 7) == 30);
        assert(*nth(h, 3) == 40);  assert(*rnth(h, 6) == 40);
        assert(*nth(h, 4) == 50);  assert(*rnth(h, 5) == 50);
        assert(*nth(h, 5) == 60);  assert(*rnth(h, 4) == 60);
        assert(*nth(h, 6) == 70);  assert(*rnth(h, 3) == 70);
        assert(*nth(h, 7) == 80);  assert(*rnth(h, 2) == 80);
        assert(*nth(h, 8) == 90);  assert(*rnth(h, 1) == 90);
        assert(*nth(h, 9) == 100); assert(*rnth(h, 0) == 100);

        std::cout << "Erase at position 1 and 5..." << std::endl;

        h.erase(it1);
        h.erase(it5);

        assert(h.size() == 8);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);  assert(*rnth(h, 7) == 10);
        assert(*nth(h, 1) == 30);  assert(*rnth(h, 6) == 30);
        assert(*nth(h, 2) == 40);  assert(*rnth(h, 5) == 40);
        assert(*nth(h, 3) == 50);  assert(*rnth(h, 4) == 50);
        assert(*nth(h, 4) == 70);  assert(*rnth(h, 3) == 70);
        assert(*nth(h, 5) == 80);  assert(*rnth(h, 2) == 80);
        assert(*nth(h, 6) == 90);  assert(*rnth(h, 1) == 90);
        assert(*nth(h, 7) == 100); assert(*rnth(h, 0) == 100);

        std::cout << "Erase two elements..." << std::endl;

        h.insert(21);
        h.insert(61);

        assert(h.size() == 10);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);  assert(*rnth(h, 9) == 10);
        assert(*nth(h, 1) == 61);  assert(*rnth(h, 8) == 61);   // THIS ELEMENT IS INSERTED 2nd
        assert(*nth(h, 2) == 30);  assert(*rnth(h, 7) == 30);
        assert(*nth(h, 3) == 40);  assert(*rnth(h, 6) == 40);
        assert(*nth(h, 4) == 50);  assert(*rnth(h, 5) == 50);
        assert(*nth(h, 5) == 21);  assert(*rnth(h, 4) == 21);   // THIS ELEMENT IS INSERTED 1st
        assert(*nth(h, 6) == 70);  assert(*rnth(h, 3) == 70);
        assert(*nth(h, 7) == 80);  assert(*rnth(h, 2) == 80);
        assert(*nth(h, 8) == 90);  assert(*rnth(h, 1) == 90);
        assert(*nth(h, 9) == 100); assert(*rnth(h, 0) == 100);
    }

    // Test erase all elements in only group in chain
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10);    (void)it0;
        auto it1 = h.insert(20);    (void)it1;
        auto it2 = h.insert(30);    (void)it2;
        auto it3 = h.insert(40);    (void)it3;

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 10); assert(*rnth(h, 3) == 10);
        assert(*nth(h, 1) == 20); assert(*rnth(h, 2) == 20);
        assert(*nth(h, 2) == 30); assert(*rnth(h, 1) == 30);
        assert(*nth(h, 3) == 40); assert(*rnth(h, 0) == 40);

        std::cout << "Erase at position 0, 1, 2 and 3..." << std::endl;

        h.erase(it0);
        h.erase(it1);
        h.erase(it2);
        h.erase(it3);

        assert(h.size() == 0);
        assert(h.capacity() == 4);

        std::cout << "Insert new elements..." << std::endl;

        h.insert(50);
        h.insert(60);
        h.insert(70);
        h.insert(80);

        assert(h.size() == 4);
        assert(h.capacity() == 4);
        assert(*nth(h, 0) == 50); assert(*rnth(h, 3) == 50);
        assert(*nth(h, 1) == 60); assert(*rnth(h, 2) == 60);
        assert(*nth(h, 2) == 70); assert(*rnth(h, 1) == 70);
        assert(*nth(h, 3) == 80); assert(*rnth(h, 0) == 80);
    }

    // Test erase all elements in first group in chain
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10);    (void)it0;
        auto it1 = h.insert(20);    (void)it1;
        auto it2 = h.insert(30);    (void)it2;
        auto it3 = h.insert(40);    (void)it3;
        auto it4 = h.insert(50);    (void)it4;
        auto it5 = h.insert(60);    (void)it5;
        auto it6 = h.insert(70);    (void)it6;
        auto it7 = h.insert(80);    (void)it7;
        auto it8 = h.insert(90);    (void)it8;
        auto it9 = h.insert(100);   (void)it9;

        assert(h.size() == 10);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);  assert(*rnth(h, 9) == 10);
        assert(*nth(h, 1) == 20);  assert(*rnth(h, 8) == 20);
        assert(*nth(h, 2) == 30);  assert(*rnth(h, 7) == 30);
        assert(*nth(h, 3) == 40);  assert(*rnth(h, 6) == 40);
        assert(*nth(h, 4) == 50);  assert(*rnth(h, 5) == 50);
        assert(*nth(h, 5) == 60);  assert(*rnth(h, 4) == 60);
        assert(*nth(h, 6) == 70);  assert(*rnth(h, 3) == 70);
        assert(*nth(h, 7) == 80);  assert(*rnth(h, 2) == 80);
        assert(*nth(h, 8) == 90);  assert(*rnth(h, 1) == 90);
        assert(*nth(h, 9) == 100); assert(*rnth(h, 0) == 100);

        std::cout << "Erase at position 0, 1, 2 and 3..." << std::endl;

        h.erase(it0);
        h.erase(it1);
        h.erase(it2);
        h.erase(it3);

        assert(h.size() == 6);
        assert(h.capacity() == 12);
        assert(*nth(h, 0) == 50);  assert(*rnth(h, 5) == 50);
        assert(*nth(h, 1) == 60);  assert(*rnth(h, 4) == 60);
        assert(*nth(h, 2) == 70);  assert(*rnth(h, 3) == 70);
        assert(*nth(h, 3) == 80);  assert(*rnth(h, 2) == 80);
        assert(*nth(h, 4) == 90);  assert(*rnth(h, 1) == 90);
        assert(*nth(h, 5) == 100); assert(*rnth(h, 0) == 100);

        std::cout << "Insert new elements..." << std::endl;

        h.insert(110);
        h.insert(120);
        h.insert(130);

        assert(h.size() == 9);
        assert(h.capacity() == 12);
        assert(*nth(h, 0) == 50);  assert(*rnth(h, 8) == 50);
        assert(*nth(h, 1) == 60);  assert(*rnth(h, 7) == 60);
        assert(*nth(h, 2) == 70);  assert(*rnth(h, 6) == 70);
        assert(*nth(h, 3) == 80);  assert(*rnth(h, 5) == 80);
        assert(*nth(h, 4) == 90);  assert(*rnth(h, 4) == 90);
        assert(*nth(h, 5) == 100); assert(*rnth(h, 3) == 100);
        assert(*nth(h, 6) == 110); assert(*rnth(h, 2) == 110);
        assert(*nth(h, 7) == 120); assert(*rnth(h, 1) == 120);
        assert(*nth(h, 8) == 130); assert(*rnth(h, 0) == 130);
    }

    // Test erase all elements in middle group in chain
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10);    (void)it0;
        auto it1 = h.insert(20);    (void)it1;
        auto it2 = h.insert(30);    (void)it2;
        auto it3 = h.insert(40);    (void)it3;
        auto it4 = h.insert(50);    (void)it4;
        auto it5 = h.insert(60);    (void)it5;
        auto it6 = h.insert(70);    (void)it6;
        auto it7 = h.insert(80);    (void)it7;
        auto it8 = h.insert(90);    (void)it8;
        auto it9 = h.insert(100);   (void)it9;

        assert(h.size() == 10);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);  assert(*rnth(h, 9) == 10);
        assert(*nth(h, 1) == 20);  assert(*rnth(h, 8) == 20);
        assert(*nth(h, 2) == 30);  assert(*rnth(h, 7) == 30);
        assert(*nth(h, 3) == 40);  assert(*rnth(h, 6) == 40);
        assert(*nth(h, 4) == 50);  assert(*rnth(h, 5) == 50);
        assert(*nth(h, 5) == 60);  assert(*rnth(h, 4) == 60);
        assert(*nth(h, 6) == 70);  assert(*rnth(h, 3) == 70);
        assert(*nth(h, 7) == 80);  assert(*rnth(h, 2) == 80);
        assert(*nth(h, 8) == 90);  assert(*rnth(h, 1) == 90);
        assert(*nth(h, 9) == 100); assert(*rnth(h, 0) == 100);

        std::cout << "Erase at position 4, 5, 6 and 7..." << std::endl;

        h.erase(it4);
        h.erase(it5);
        h.erase(it6);
        h.erase(it7);

        assert(h.size() == 6);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);  assert(*rnth(h, 5) == 10);
        assert(*nth(h, 1) == 20);  assert(*rnth(h, 4) == 20);
        assert(*nth(h, 2) == 30);  assert(*rnth(h, 3) == 30);
        assert(*nth(h, 3) == 40);  assert(*rnth(h, 2) == 40);
        assert(*nth(h, 4) == 90);  assert(*rnth(h, 1) == 90);
        assert(*nth(h, 5) == 100); assert(*rnth(h, 0) == 100);

        std::cout << "Insert new elements..." << std::endl;

        h.insert(110);
        h.insert(120);
        h.insert(130);

        assert(h.size() == 9);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);  assert(*rnth(h, 8) == 10);
        assert(*nth(h, 1) == 20);  assert(*rnth(h, 7) == 20);
        assert(*nth(h, 2) == 30);  assert(*rnth(h, 6) == 30);
        assert(*nth(h, 3) == 40);  assert(*rnth(h, 5) == 40);
        assert(*nth(h, 4) == 90);  assert(*rnth(h, 4) == 90);
        assert(*nth(h, 5) == 100); assert(*rnth(h, 3) == 100);
        assert(*nth(h, 6) == 110); assert(*rnth(h, 2) == 110);
        assert(*nth(h, 7) == 120); assert(*rnth(h, 1) == 120);
        assert(*nth(h, 8) == 130); assert(*rnth(h, 0) == 130);
    }

    // Test erase only element in last group in chain
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10);    (void)it0;
        auto it1 = h.insert(20);    (void)it1;
        auto it2 = h.insert(30);    (void)it2;
        auto it3 = h.insert(40);    (void)it3;
        auto it4 = h.insert(50);    (void)it4;
        auto it5 = h.insert(60);    (void)it5;
        auto it6 = h.insert(70);    (void)it6;
        auto it7 = h.insert(80);    (void)it7;
        auto it8 = h.insert(90);    (void)it8;

        assert(h.size() == 9);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);   assert(*rnth(h, 8) == 10);
        assert(*nth(h, 1) == 20);   assert(*rnth(h, 7) == 20);
        assert(*nth(h, 2) == 30);   assert(*rnth(h, 6) == 30);
        assert(*nth(h, 3) == 40);   assert(*rnth(h, 5) == 40);
        assert(*nth(h, 4) == 50);   assert(*rnth(h, 4) == 50);
        assert(*nth(h, 5) == 60);   assert(*rnth(h, 3) == 60);
        assert(*nth(h, 6) == 70);   assert(*rnth(h, 2) == 70);
        assert(*nth(h, 7) == 80);   assert(*rnth(h, 1) == 80);
        assert(*nth(h, 8) == 90);   assert(*rnth(h, 0) == 90);

        std::cout << "Erase at position 8..." << std::endl;

        h.erase(it8);

        assert(h.size() == 8);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);   assert(*rnth(h, 7) == 10);
        assert(*nth(h, 1) == 20);   assert(*rnth(h, 6) == 20);
        assert(*nth(h, 2) == 30);   assert(*rnth(h, 5) == 30);
        assert(*nth(h, 3) == 40);   assert(*rnth(h, 4) == 40);
        assert(*nth(h, 4) == 50);   assert(*rnth(h, 3) == 50);
        assert(*nth(h, 5) == 60);   assert(*rnth(h, 2) == 60);
        assert(*nth(h, 6) == 70);   assert(*rnth(h, 1) == 70);
        assert(*nth(h, 7) == 80);   assert(*rnth(h, 0) == 80);

        std::cout << "Insert new elements..." << std::endl;

        h.insert(110);
        h.insert(120);
        h.insert(130);
        h.insert(140);

        assert(h.size() == 12);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);   assert(*rnth(h, 11) == 10);
        assert(*nth(h, 1) == 20);   assert(*rnth(h, 10) == 20);
        assert(*nth(h, 2) == 30);   assert(*rnth(h, 9) == 30);
        assert(*nth(h, 3) == 40);   assert(*rnth(h, 8) == 40);
        assert(*nth(h, 4) == 50);   assert(*rnth(h, 7) == 50);
        assert(*nth(h, 5) == 60);   assert(*rnth(h, 6) == 60);
        assert(*nth(h, 6) == 70);   assert(*rnth(h, 5) == 70);
        assert(*nth(h, 7) == 80);   assert(*rnth(h, 4) == 80);
        assert(*nth(h, 8) == 110);  assert(*rnth(h, 3) == 110);
        assert(*nth(h, 9) == 120);  assert(*rnth(h, 2) == 120);
        assert(*nth(h, 10) == 130); assert(*rnth(h, 1) == 130);
        assert(*nth(h, 11) == 140); assert(*rnth(h, 0) == 140);
    }

    // Test erase all elements in last group in chain
    {
        plf::hive<int> h(plf::hive_limits(4, 128));

        std::cout << "Insert initial elements..." << std::endl;

        auto it0 = h.insert(10);    (void)it0;
        auto it1 = h.insert(20);    (void)it1;
        auto it2 = h.insert(30);    (void)it2;
        auto it3 = h.insert(40);    (void)it3;
        auto it4 = h.insert(50);    (void)it4;
        auto it5 = h.insert(60);    (void)it5;
        auto it6 = h.insert(70);    (void)it6;
        auto it7 = h.insert(80);    (void)it7;
        auto it8 = h.insert(90);    (void)it8;
        auto it9 = h.insert(100);   (void)it9;

        assert(h.size() == 10);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);   assert(*rnth(h, 9) == 10);
        assert(*nth(h, 1) == 20);   assert(*rnth(h, 8) == 20);
        assert(*nth(h, 2) == 30);   assert(*rnth(h, 7) == 30);
        assert(*nth(h, 3) == 40);   assert(*rnth(h, 6) == 40);
        assert(*nth(h, 4) == 50);   assert(*rnth(h, 5) == 50);
        assert(*nth(h, 5) == 60);   assert(*rnth(h, 4) == 60);
        assert(*nth(h, 6) == 70);   assert(*rnth(h, 3) == 70);
        assert(*nth(h, 7) == 80);   assert(*rnth(h, 2) == 80);
        assert(*nth(h, 8) == 90);   assert(*rnth(h, 1) == 90);
        assert(*nth(h, 9) == 100);  assert(*rnth(h, 0) == 100);

        std::cout << "Erase at position 8 and 9..." << std::endl;

        h.erase(it8);
        h.erase(it9);

        assert(h.size() == 8);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);   assert(*rnth(h, 7) == 10);
        assert(*nth(h, 1) == 20);   assert(*rnth(h, 6) == 20);
        assert(*nth(h, 2) == 30);   assert(*rnth(h, 5) == 30);
        assert(*nth(h, 3) == 40);   assert(*rnth(h, 4) == 40);
        assert(*nth(h, 4) == 50);   assert(*rnth(h, 3) == 50);
        assert(*nth(h, 5) == 60);   assert(*rnth(h, 2) == 60);
        assert(*nth(h, 6) == 70);   assert(*rnth(h, 1) == 70);
        assert(*nth(h, 7) == 80);   assert(*rnth(h, 0) == 80);

        std::cout << "Insert new elements..." << std::endl;

        h.insert(110);
        h.insert(120);
        h.insert(130);
        h.insert(140);

        assert(h.size() == 12);
        assert(h.capacity() == 16);
        assert(*nth(h, 0) == 10);   assert(*rnth(h, 11) == 10);
        assert(*nth(h, 1) == 20);   assert(*rnth(h, 10) == 20);
        assert(*nth(h, 2) == 30);   assert(*rnth(h, 9) == 30);
        assert(*nth(h, 3) == 40);   assert(*rnth(h, 8) == 40);
        assert(*nth(h, 4) == 50);   assert(*rnth(h, 7) == 50);
        assert(*nth(h, 5) == 60);   assert(*rnth(h, 6) == 60);
        assert(*nth(h, 6) == 70);   assert(*rnth(h, 5) == 70);
        assert(*nth(h, 7) == 80);   assert(*rnth(h, 4) == 80);
        assert(*nth(h, 8) == 110);  assert(*rnth(h, 3) == 110);
        assert(*nth(h, 9) == 120);  assert(*rnth(h, 2) == 120);
        assert(*nth(h, 10) == 130); assert(*rnth(h, 1) == 130);
        assert(*nth(h, 11) == 140); assert(*rnth(h, 0) == 140);
    }
}
