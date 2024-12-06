#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include <set>
#include <utility>
#include <algorithm>
#include <functional>

std::pair<int, int> next_pos(int y, int x, int direction) {
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

//std::optional<std::pair<int, int>> cycle_detection(std::vector<std::vector<char>> map, int y, int x, int direction) {
//    std::set<std::tuple<int,int,int>> visited{};
//
//    auto next = next_pos(x,y, direction);
//    if (!get_position(map, next.first, next.second).has_value()) {
//        return std::nullopt;
//    }
//    map[next.first][next.second] = '#';
//
//    int obstacle_y = next.first;
//    int obstacle_x = next.second;
//
//    while (true) {
//        //std::cout << "y: " << y << ", x: " << x << ", direction: " << direction << std::endl;
//        auto next = next_pos(x,y, direction);
//        auto n = get_position(map, next.first, next.second);
//        
//        if (!n.has_value()) {
//            break;
//        }
//        
//
//        auto v = n.value();
//        if (v != '#') {
//            x = next.second;
//            y = next.first;
//            auto search = std::make_tuple(y, x, direction);
//            if (std::find(visited.begin(), visited.end(), search) != visited.end()) {
//                return std::make_pair(obstacle_y, obstacle_x);
//            }
//        }
//        else {
//            direction = rotate(direction);
//        }
//        visited.insert(std::make_tuple(y, x, direction));
//
//    }
//
//    return std::nullopt;
//}

std::optional<std::vector<std::tuple<int, int, int>>> walk(const std::vector<std::vector<char>>& map, int y, int x, int direction) {
    std::vector<std::tuple<int, int, int>> visited{};
    while (true) {
        //std::cout << "y: " << y << ", x: " << x << ", direction: " << direction << std::endl;
        auto f = std::find(visited.begin(), visited.end(), std::make_tuple(y, x, direction));
        if (f != visited.end()) {
            //std::cout << "cycle" << std::endl;
            return std::nullopt;
        }
        visited.push_back(std::make_tuple(y, x, direction));

        auto next = next_pos(y, x, direction);
        auto n = get_position(map, next.first, next.second);

        if (!n.has_value()) {
            break;
        }
        
        auto v = n.value();
        if (v != '#') {
            x = next.second;
            y = next.first;
        }
        else {
            direction = rotate(direction);
        }

    }
    
    //std::cout << "no cycle" << std::endl;
    return visited;
}




int main(int argc, char* argv[]) {
    std::ifstream infile(argv[1]);
    
    std::vector<std::vector<char>> map{};
    std::string line{};
    while (std::getline(infile, line)) {
        std::vector<char> row{line.begin(), line.end()};
        map.push_back(row);
    }
    

    int start_y = 0;
    int start_x = 0;
    int start_direction = 0;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j]== '^') {
                start_y = i;
                start_x = j;
            }
        }
    }
    
    
    auto visited = walk(map, start_y, start_x, start_direction);
    std::vector<std::vector<char>> map_copy{};
    std::set<std::pair<int, int>> obstacles{};

    for (auto v : visited.value()) {
        map_copy = map;
        auto y = std::get<0>(v);
        auto x = std::get<1>(v);
        auto direction = std::get<2>(v);
        
        map_copy[y][x] = '#';
    
        //std::cout << "========================" << std::endl;
        //for(auto m: map_copy) {
        //    for (auto c: m) {
        //        std::cout << c;
        //    }
        //    std::cout << std::endl;
        //}
        if (walk(map_copy, start_y, start_x, start_direction) == std::nullopt) {
            obstacles.insert(std::make_pair(y,x));
        }

    }

    std::cout << visited.value().size() << std::endl;
    std::cout << obstacles.size() << std::endl;

    return 0;
}
