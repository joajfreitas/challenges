#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <deque>

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

int get_price(int value) {
    return value % 10;
}

void insert_cache(Cache& cache, int seed) {
    std::deque<int> price_changes{};

    for (int i=1; i<2000; i++) {
        std::cout << "seed: " << seed << std::endl;
        auto previous = get_price(data[i-1]);
        auto current = get_price(data[i]);
        price_changes.push_back(current - previous);
        if (price_changes.size() > 4) {
            price_changes.pop_front();
            auto key = std::make_tuple(price_changes[0], price_changes[1], price_changes[2], price_changes[3]);
            if (cache.find(key) != cache.end()) {
                cache[key].push_back(current);
            } else {
                cache[key] = {current};
            }
        }
        seed = pseudo_random(seed);
    }
}

int main() {
    //std::vector<int> data = {
    //    1,
    //    10,
    //    100,
    //    2024
    //};
    
    std::vector<int> data = {
        1,2,3,2024
    };

    Cache cache{}; 
    
    insert_cache(cache, 123);

    //for(auto [key, value] : cache) {
    //    std::cout << "key: " << std::get<0>(key) << " " << std::get<1>(key) << " " << std::get<2>(key) << " " << std::get<3>(key) << std::endl;
    //    for (auto v : value) {
    //        std::cout << "value: " << v << std::endl;
    //    }
    //}

    //long long unsigned acc = 0;
    //for (auto n : data) {
    //    acc += apply(n, 2000, cache);
    //}

    //std::cout << "acc: " << acc << std::endl;
    return 0;

}
