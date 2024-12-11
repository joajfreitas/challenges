#include <vector>
#include <cmath>
#include <iostream>


int number_of_digits(int number) {
    return std::log10(number) + 1;
}

long int iter(long int i, int depth) {
    std::cout << "i: " << i << std::endl;
    if (depth == 0) {
        return 1;
    }

    if (i == 0) {
        return iter(1, depth-1); 
    }

    auto n_digits = number_of_digits(i);
    std::cout << "i: " << i << std::endl;
    std::cout << "number of digits: " << n_digits << "\n";

    long int acc = 0;
    if (n_digits % 2 == 0) {
        acc += iter(i % static_cast<long int>(std::pow(10, n_digits/2)), depth-1);
        acc += iter(i / static_cast<long int>(std::pow(10, n_digits/2)), depth-1);
        return acc;
    }

    return iter(i * 2024, depth-1);
}

int main() {

    std::vector<int> data = {125,17};

    long int acc = 0;

    for (int i=0; i<data.size(); i++) {
        acc += iter(i, 6);
    }

    std::cout << "acc: "<< acc << std::endl;


    
    return 0;
}
