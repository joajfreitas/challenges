#include <cmath>
#include <iostream>
#include <optional>

#include "data.h"

bool is_increasing(const std::vector<int>& line) {
    for (auto i = line.begin(); i != line.end() - 1; i++) {
        if (*(i+1) - *i < 0){
            return false;
        }
    }

    return true;
}

bool is_decreasing(const std::vector<int>& line) {
    for (auto i = line.begin(); i != line.end() - 1; i++) {
        if (*(i+1) - *i > 0){
            return false;
        }
    }

    return true;
}

bool is_derivative_within_bounds(const std::vector<int>& line) {
    for (auto i = line.begin(); i != line.end() - 1; i++) {
        auto diff = std::abs(*(i+1) - *i);
        if (!(diff <= 3 && diff >= 1)){
            return false;
        }
    }

    return true;
}

bool is_valid(const std::vector<int>& line) {
    return (is_increasing(line) || is_decreasing(line)) && is_derivative_within_bounds(line);
}

int main() {
    
    int acc = 0;
    for (auto row: data) {
        acc += is_valid(row);
    }


    std::cout << acc << std::endl;
    
    acc = 0;
    for (auto row: data) {
        bool is_valid_row = false;
        for (int i=0; i<row.size(); i++) {
            std::vector<int> row_copy = row;

            row_copy.erase(row_copy.begin() + i);
            if (is_valid(row_copy)) {
                is_valid_row = true;
            }
        }

        acc += is_valid_row;
    }

    std::cout << acc << std::endl;

    return 0;
}
