#include <iostream>

#include "data.h"
#include "data2.h"

int main() {
    int acc = 0;
    for (const auto& [x, y]: data) {
        acc += x * y;
    }
    std::cout << acc << std::endl;

    acc = 0;
    bool enabled = true;
    for (const auto& [instruction, x, y]: data2) {
        if (instruction == Instruction::mul && enabled) {
            acc += x * y;
        }
        else if (instruction == Instruction::dont) {
            enabled = false;
        }
        else if (instruction == Instruction::do_) {
            enabled = true;
        }
    }
    std::cout << acc << std::endl;

    return 0;
}
