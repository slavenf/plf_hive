.PHONY: all
all:
	g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../plf_bitsets plf_hive_test_suite.cpp -o plf_hive_test_suite
	./plf_hive_test_suite
