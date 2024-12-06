#include <iostream>
#include <vector>

#include "data.h"

bool check_pair(int a, int b, const std::vector<std::pair<int, int>>& rules) {
    for (auto& rule: rules) {
        if (a == rule.second && b == rule.first) {
            return false;
        }
    }

    return true;
} 

std::tuple<bool, int, int> check_validity(const std::vector<std::pair<int, int>>& rules, const std::vector<int>& update) {
    std::tuple<bool,int,int> valid = std::make_tuple(true,0,0);
    for (int i=1; i<update.size(); i++) {
        for (int j=0; j<i; j++) {
            if (!check_pair(update[j], update[i], rules)) {
                valid = std::make_tuple(false, i, j);
            }
        }
    }

    return valid;
}

void order(std::vector<int>& update, const std::vector<std::pair<int, int>>& rules) {
    while (true) {
        auto valid = check_validity(rules, update);
        if (std::get<0>(valid)) {
            return;
        }

        auto i = std::get<1>(valid);
        auto j = std::get<2>(valid);
    

        auto swp = update[i];
        update[i] = update[j];
        update[j] = swp;
    }
}

int main() {
    int acc = 0;
    for (const auto& update: updates) {
        if (std::get<0>(check_validity(rules, update))) {
            acc += update[update.size()/2];
        }
    }

    std::cout << acc << std::endl;
    
    acc = 0;
    for (auto& update: updates) {
        auto valid = check_validity(rules, update);
        if (std::get<0>(valid)) {
            continue;
        }
        order(update, rules);
        acc += update[update.size()/2];
    }

    std::cout << acc << std::endl;

    return 0;
}
