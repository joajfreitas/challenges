#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include <set>
#include <utility>
#include <functional>

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

bool walk(const std::vector<std::vector<char>>& map, std::set<std::tuple<int,int,int>>& visited, int y, int x, int direction, std::function<bool(int, int, int)> stop_condition) {
    while (true) {
        //std::cout << "y: " << y << ", x: " << x << ", direction: " << direction << std::endl;
        if (stop_condition(y,x,direction)) {
            return true;
        }
        auto next = next_pos(x,y, direction);
        auto n = get_position(map, next.first, next.second);
        
        if (!n.has_value()) {
            break;
        }
        
        visited.insert(std::make_tuple(y, x, direction));

        auto v = n.value();
        if (v != '#') {
            x = next.second;
            y = next.first;
        }
        else {
            direction = rotate(direction);
            auto next = next_pos(x,y, direction);
            x = next.second;
            y = next.first;
        }

    }

    return false;
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
    
    std::set<std::tuple<int, int, int>> visited{};
    std::set<std::pair<int, int>> obstacles = {};
    walk(map, visited, y, x, direction, [&visited, &obstacles, &map](int y, int x, int direction) {
        std::set<std::tuple<int, int, int>> visited_copy = visited;
        std::vector<std::vector<char>> map_copy = map;
        
        auto n = next_pos(x,y, direction);
        if (!get_position(map, n.first, n.second).has_value()) {
            return false;
        }
        map_copy[n.first][n.second] = '#';
        //std::cout << "calling inner walk" << std::endl;
        if (walk(map_copy, visited_copy, y, x, direction, [&visited_copy](int y, int x, int direction) {
            return visited_copy.find(std::make_tuple(y, x, direction)) != visited_copy.end();
        })) {
            obstacles.insert(std::make_pair(n.first, n.second));
        }
        return false;
    });
    std::cout << visited.size() << std::endl;
    
    for (auto o : obstacles) {
        std::cout << o.first << ", " << o.second << std::endl;
    }
    std::cout << obstacles.size() << std::endl;


    return 0;
}
