#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

#include "data.h"

// check that string matches a combination of patterns
long long int check(std::unordered_map<std::string, long long int>& cache, const std::vector<std::string>& patterns, std::string str, int index) {
    
    std::string sub = str.substr(index, str.size()-index);
    if (cache.find(sub) != cache.end()) {
        return cache[sub];
    }

    if (index == str.size()) {
        cache[sub] = 1;
        return 1;
    }
    
    long long int acc = 0;
    for (const std::string& pattern : patterns) {
        if (str.substr(index, pattern.size()) == pattern) {
            acc += check(cache, patterns, str, index + pattern.size());
        }
    }
    
    cache[sub] = acc;
    return acc;
}


int main() {
    //std::vector<std::string> patterns = {
    //    "r", "wr", "b", "g", "bwu", "rb", "gb", "br"
    //};
    //
    //std::vector<std::string> lines = {
    //    "brwrr",
    //    "bggr",
    //    "gbbr",
    //    "rrbgbr",
    //    "ubwu",
    //    "bwurrg",
    //    "brgr",
    //    "bbrgwb"
    //};
    
    long long int acc = 0;

    std::unordered_map<std::string, long long int> cache{};
    for (auto& line : lines) {
        acc += check(cache, patterns, line, 0);
    }

    std::cout << "acc: " << acc << std::endl;
    return 0;
}

