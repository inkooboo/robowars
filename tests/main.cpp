#include "cpp_defs.hpp"
#include <map>
#include <string>

typedef bool(unit_test_func_t)();
std::map<std::string, unit_test_func_t *> unit_tests_map;

#define ADD_UNIT_TEST(unit_test_function_name) \
    extern bool unit_test_function_name(); \
    unit_tests_map[#unit_test_function_name] = unit_test_function_name;


int main(int argc, char *argv[])
{
    unused_params(argc, argv);

    ADD_UNIT_TEST(unit_test_packetyzer)


    return 0;
}
