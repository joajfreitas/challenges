#include <iostream>

#include "datatypes.h"
#include "data.h"
//#include "example.h"

void print_map(const Map& map) {
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

char get_point(const Map& map, const Point& point) {
    if (point.first < 0 || point.first >= map.size() || point.second < 0 || point.second >= map[0].size()) {
        return '.';
    }
    return map[point.first][point.second];
}

bool check_diff(const Map& map, const Point& point1, const Point& point2) {
    auto p1 = get_point(map, point1);
    auto p2 = get_point(map, point2);

    if (p2 == '.') {
        return false;
    }
    else if (p2 - p1 != 1) {
        return false;
    }
    else {
        return true;

    }
}

int dfs(const Map& map, Visited& visited, Point point) {
    if (point.first < 0 || point.first >= map.size() || point.second < 0 || point.second >= map[0].size()) {
        return 0;
    }
    //if (visited.find(point) != visited.end()) {
    //    return 0;
    //}
    //visited.insert(point);
    if (map[point.first][point.second] == '9') {
        //print_map(map);
        //std::cout << "===============" << std::endl;
        return 1;
    }
    int acc = 0;
    Point north = std::make_pair(point.first-1, point.second);
    Point south = std::make_pair(point.first+1, point.second);
    Point west = std::make_pair(point.first, point.second-1);
    Point east = std::make_pair(point.first, point.second+1);
    
    if (check_diff(map, point, north)) {
        acc += dfs(map, visited, north);
    }
    if (check_diff(map, point, south)) {
        acc += dfs(map, visited, south);
    }
    if (check_diff(map, point, west)) {
        acc += dfs(map, visited, west);
    }
    if (check_diff(map, point, east)) {
        acc += dfs(map, visited, east);
    }

    return acc;
}

int main() {
    
    Map map{};
    for (const auto& row : data) {
        Row row_{};
        for (const auto& cell : row) {
            row_.push_back(cell);
        }
        map.push_back(row_);
    }
    
    
    int acc = 0;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j] == '0') {
                Visited reached{};
                //std::cout << "Searching from: " << i << "," << j << std::endl;
                int v = dfs(map, reached, std::make_pair(i,j));
                acc += v;
                //std::cout << "reached: " << v << std::endl;
            }
        }
    }

    std::cout << "acc: " << acc << std::endl;
    return 0;
}
