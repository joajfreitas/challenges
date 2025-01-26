#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include <unordered_map>

#include "data.h"


using Key = std::tuple<int, int, int, int>;

struct KeyHash
{
    std::size_t operator()(const Key& k) const
    {
        return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k) ^ std::get<3>(k);
    }
};

struct KeyEqual
{
    std::size_t operator()(const Key& left, const Key& right) const
    {
        return 
            (std::get<0>(left) == std::get<0>(right)) && 
            (std::get<1>(left) == std::get<1>(right)) && 
            (std::get<2>(left) == std::get<2>(right)) && 
            (std::get<3>(left) == std::get<3>(right));
    }
};


typedef std::unordered_map<Key,std::vector<int>,KeyHash,KeyEqual> Cache;

long long unsigned pseudo_random(long long unsigned seed) {
    seed = ((seed << 6) ^ seed) % 16777216;
    seed = ((seed >> 5) ^ seed) % 16777216;
    return ((seed << 11) ^ seed) % 16777216;
}

long long unsigned apply(long long unsigned seed, int n, Cache& cache) {
    for (int i=0; i<n; i++) {
        seed = pseudo_random(seed);
    }

    return seed;
}

int main() {
    std::vector<int> data = {
        1,
        10,
        100,
        2024
    };

    Cache cache{}; 
    
    long long unsigned acc = 0;
    for (auto n : data) {
        acc += apply(n, 2000, cache);
    }

    std::cout << "acc: " << acc << std::endl;
    return 0;

}
