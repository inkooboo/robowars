#include "cpp_defs.hpp"
#include <map>
#include <string>
#include <iostream>
#include <locale>
#include <clocale>

typedef bool(unit_test_func_t)();
std::map<std::string, unit_test_func_t *> unit_tests_map;

#define ADD_UNIT_TEST(unit_test_function_name) \
    extern bool unit_test_function_name(); \
    unit_tests_map[#unit_test_function_name] = unit_test_function_name;


int main(int argc, char *argv[])
{
    unused_params(argc, argv);

    std::setlocale( LC_ALL, "English" );

    ADD_UNIT_TEST(unit_test_packetyzer)

    for (auto &test_pair : unit_tests_map)
    {
        const std::string &name = test_pair.first;
        unit_test_func_t *func = test_pair.second;

        std::cout << name << ": \n" << (func() ? "ok" : "fail") << std::endl;
    }

    return 0;
}
