#include <optional>
#include <stdexcept>
#include <iostream>
#include <bitset>
#include "input.h"

bool contains(std::map<std::string, std::optional<int>>& mem, std::string key) {
    return mem.find(key) != mem.end();
}

bool check_is_solved(std::map<std::string, std::optional<int>>& mem) {
    for (auto& [key, value] : mem) {
        if (value == std::nullopt) {
            return false;
        }
    }
    return true;
}

long unsigned get_number(std::map<std::string, std::optional<int>>& mem) {
    long unsigned i = 0;
    long unsigned n = 0;
    for (auto& [key, value] : mem) {
        if (key[0] == 'z') {
            n |= ((long unsigned) value.value()) << i;
            i++;
        }

    }

    return n;
}

int apply(std::string op, int x, int y) {
    if (op == "AND") {
        return x & y;
    } else if (op == "OR") {
        return x | y;
    } else if (op == "XOR") {
        return x ^ y;
    } else {
        throw std::runtime_error("Unknown operation: " + op);
    }
}


int main() {
    std::map<std::string, std::optional<int>> mem{};

    for (auto& [key, value] : init_values) {
        mem[key] = value;
    }

    for (auto& [x, op, y, z] : chain) {
        if (!contains(mem, x)) {
            mem[x] = std::nullopt;
        }
        if (!contains(mem, y)) {
            mem[y] = std::nullopt;
        }
        if (!contains(mem, z)) {
            mem[z] = std::nullopt;
        }

    }

    while(!check_is_solved(mem)) {
        for (auto& [x, op, y, z] : chain) {
            if (mem[z] != std::nullopt) {
                continue;
            }
            
            if (mem[x] == std::nullopt || mem[y] == std::nullopt) {
                continue;
            }

            mem[z] = apply(op, mem[x].value(), mem[y].value());
        }
    }
    
    for (auto& [key, value] : mem) {
        if (value != std::nullopt) {
            std::cout << key << " = " << value.value() << std::endl;
        }
        else {
            std::cout << key << " = " << "nullopt" << std::endl;
        }
    }

    //std::cout << "Number: " << get_number(mem) << std::endl;

    return  0;
}
