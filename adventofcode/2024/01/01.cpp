#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "data.h"

int main()
{

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    std::unordered_map<int, int> freqs {};
    freqs.reserve(left.size());

    // compute frequencies beforehand
    std::for_each(right.begin(), right.end(), [&freqs](auto right) {
        if (freqs.find(right) == freqs.end()) {
            freqs[right] = 1;
        } else {
            freqs[right]++;
        }
    });
    
    int diffs_count = 0;
    int freqs_count = 0;
    for (int i=0; i<left.size(); i++) {
        diffs_count += std::abs(left[i] - right[i]);
        freqs_count += left[i] * freqs[left[i]];
    }

    std::cout << diffs_count << std::endl;
    std::cout << freqs_count << std::endl;

    return 0;
}
