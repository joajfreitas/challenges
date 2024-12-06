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

std::optional<std::pair<int, int>> beam_search(const std::vector<std::vector<char>>& map, const std::set<std::tuple<int,int,int>>& visited, int x, int y, int direction) {

    std::cout << "search start: " << y << " " << x << " " << direction << std::endl;
    //for (const auto& v : visited) {
        //std::cout << "[" << std::get<0>(v) << " " << std::get<1>(v) << " " << std::get<2>(v) <<"], " << std::endl;
    //}
    int og_x = x;
    int og_y = y;
    while (true) {
        if (!get_position(map, y, x).has_value()) {
            break;
        }

        if (visited.find(std::make_tuple(y,x,direction)) != visited.end()) {
            return std::make_pair(og_y, og_x);
        }
        auto r = next_pos(x,y,direction);
        y = r.first;
        x = r.second;

    }
    return std::nullopt;
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
    
    std::set<std::tuple<int, int, int>> visited{{y,x, 0}};

    std::set<std::pair<int, int>> obstacles = {};
    while (true) {
        auto next = next_pos(x,y, direction);
        auto n = get_position(map, next.first, next.second);
        
        if (!n.has_value()) {
            break;
        }

        auto v = n.value();
    
        if (v != '#') {
            auto r = beam_search(map, visited, x, y, rotate(direction));
            if (r.has_value()){
                //std::cout << "y: " << r.value().first << ", ";
                //std::cout << "x: " << r.value().second << std::endl;
                auto z = next_pos(r.value().second, r.value().first, direction);
                std::cout << "y: " << z.first << ", ";
                std::cout << "x: " << z.second << std::endl;
                obstacles.insert(std::make_pair(z.first, z.second));
            }
            x = next.second;
            y = next.first;
            visited.insert(std::make_tuple(y, x, direction));
        }
        else {
            visited.insert(std::make_tuple(y, x, direction));
            direction = rotate(direction);
        }
    }

    std::cout << visited.size() << std::endl;
    std::cout << "obstacles: " << obstacles.size() << std::endl;


    return 0;
}
