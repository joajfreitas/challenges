#include <vector>
#include <string>
#include <map>
#include <array>


std::map<std::string, int> init_values = {
    {"x00", 1},
    {"x01", 1},
    {"x02", 1},
    {"y00", 0},
    {"y01", 1},
    {"y02", 0}
};

std::vector<std::array<std::string, 4>> chain = {
    std::array<std::string, 4>{"x00", "AND",  "y00", "z00"},
    std::array<std::string, 4>{"x01", "XOR",  "y01", "z01"},
    std::array<std::string, 4>{"x02", "OR",   "y02", "z02"}
};
