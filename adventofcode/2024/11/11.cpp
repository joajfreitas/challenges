#include <vector>
#include <cmath>
#include <iostream>

#include <map>
#include <utility>

using Cache = std::map<std::pair<long long int, int>, long int>;

long long int number_of_digits(long long int number) {
    return std::log10(number) + 1;
}

long long int iter(long long int i, int depth, Cache& cache) {
    if (depth == 0) {
        cache[std::make_pair(i, depth)] = 1;
        return 1;
    }

    if (cache.find(std::make_pair(i, depth)) != cache.end()) {
        return cache[std::make_pair(i, depth)];
    }


    if (i == 0) {
        auto v = iter(1, depth-1, cache); 
        cache[std::make_pair(i, depth)] = v;
        return v;
    }

    auto n_digits = number_of_digits(i);

    long long int acc = 0;
    if (n_digits % 2 == 0) {
        acc += iter(i % static_cast<long long int>(std::pow(10LL, n_digits/2LL)), depth-1, cache);
        acc += iter(i / static_cast<long long int>(std::pow(10LL, n_digits/2LL)), depth-1, cache);

        cache[std::make_pair(i, depth)] = acc;
        return acc;
    }

    auto v = iter(i * 2024LL, depth-1, cache);
    cache[std::make_pair(i, depth)] = v;
    return v;
}

int main(int argc, char* argv[]) {
    std::vector<int> data = {6571,0,5851763,526746,23,69822,9,989};

     Cache cache{};
    
        long long int acc = 0;

    for (int i=0; i<data.size(); i++) {
        acc += iter(data[i], std::stoi(argv[1]), cache);
    }
    std::cout << "acc: "<< acc << std::endl;

    return 0;
}
