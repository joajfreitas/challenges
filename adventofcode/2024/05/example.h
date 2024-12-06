#include <vector>
#include <utility>

std::vector<std::pair<int, int>> rules = {
    std::make_pair(47,53),
    std::make_pair(97,13),
    std::make_pair(97,61),
    std::make_pair(97,47),
    std::make_pair(75,29),
    std::make_pair(61,13),
    std::make_pair(75,53),
    std::make_pair(29,13),
    std::make_pair(97,29),
    std::make_pair(53,29),
    std::make_pair(61,53),
    std::make_pair(97,53),
    std::make_pair(61,29),
    std::make_pair(47,13),
    std::make_pair(75,47),
    std::make_pair(97,75),
    std::make_pair(47,61),
    std::make_pair(75,61),
    std::make_pair(47,29),
    std::make_pair(75,13),
    std::make_pair(53,13)
};


std::vector<std::vector<int>> updates = {
    std::vector<int>{75,47,61,53,29},
    std::vector<int>{97,61,53,29,13},
    std::vector<int>{75,29,13},
    std::vector<int>{75,97,47,61,53},
    std::vector<int>{61,13,29},
    std::vector<int>{97,13,75,29,47}
};
