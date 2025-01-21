#include <iostream>

#include "data.h"
//#include "example.h"

int main()
{
    std::vector<std::vector<int>> keys {};
    std::vector<std::vector<int>> locks {};

    for (const auto& schematic : input) {
        std::vector<int> tmp { 0, 0, 0, 0, 0 };
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 5; j++) {
                if (schematic[i][j] == '#') {
                    tmp[j] += 1;
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            tmp[i] -= 1;
        }

        if (schematic[0] == "#####") {
            locks.push_back(tmp);
        } else {
            keys.push_back(tmp);
        }
    }

    int acc = 0;
    for (const auto& lock : locks) {
        for (const auto& key : keys) {
            bool match = true;
            for (int i = 0; i < 5; i++) {
                if (lock[i] + key[i] > 5) {
                    match = false;
                }
            }

            if (match) {
                acc += 1;
            }
        }
    }

    std::cout << acc << std::endl;
    return 0;
}
