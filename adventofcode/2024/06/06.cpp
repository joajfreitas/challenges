#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include <set>
#include <utility>

std::pair<int, int> next_pos(int x, int y, int direction) {
    if (direction == 0) {
        y -= 1;
    }
    else if (direction == 1) {
        x += 1;
    }
    else if (direction == 2) {
        y += 1;
    }
    else if (direction == 3) {
        x -= 1;
    }

    return std::make_pair(y, x);
}

int rotate(int direction) {
    return (direction + 1) % 4;
}

std::optional<char> get_position(const std::vector<std::vector<char>>& map, int y, int x) {
    if (map.size() <= y || y < 0  || map[y].size() <= x || x < 0) {
        return std::nullopt;
    }

    return map[y][x];
}

int main(int argc, char* argv[]) {
    std::ifstream infile(argv[1]);
    
    std::vector<std::vector<char>> map{};
    std::string line{};
    while (std::getline(infile, line)) {
        std::vector<char> row{line.begin(), line.end()};
        map.push_back(row);
    }
    

    int y = 0;
    int x = 0;
    int direction = 0;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j]== '^') {
                y = i;
                x = j;
            }
        }
    }
    
    std::set<std::pair<int, int>> visited{{y,x}};
    while (true) {
        auto next = next_pos(x,y, direction);
        auto n = get_position(map, next.first, next.second);
        
        if (!n.has_value()) {
            break;
        }

        auto v = n.value();
    
        if (v != '#') {
            x = next.second;
            y = next.first;
            visited.insert(std::make_pair(y, x));
        }
        else {
            direction = rotate(direction);
        }
    }

    std::cout << visited.size() << std::endl;


    return 0;
}
