#include <iostream>
#include <utility>
#include <set>

#include "data.h"

bool bound_check(const std::vector<std::vector<char>>& map, int y, int x) {
    return !(y < 0 || y >= map.size() || x < 0 || x >= map[y].size());
}

char get_pos(const std::vector<std::vector<char>>& map, int y, int x) {
    if (!bound_check(map, y, x)) {
        return '.';
    }
    return map[y][x];
}

int main() {
    std::vector<std::vector<char>> map{};

    for (const auto& line : data) {
        map.push_back(std::vector<char>{line.begin(), line.end()});
    }
    
    std::set<std::tuple<int, int, char>> antennas{};

    for (int y=0; y<map.size(); y++) {
        for (int x=0; x<map[y].size(); x++) {
            if (get_pos(map, y, x) != '.') {
                antennas.insert(std::make_tuple(y, x, get_pos(map, y, x)));
            }
        }
    }
    

    std::set<std::pair<int, int>> antinodes{};
    for (const auto& antenna1: antennas) {
        std::cout << "Antenna at (" << std::get<0>(antenna1) << ", " << std::get<1>(antenna1) << ") is on frequency " << std::get<2>(antenna1) << std::endl;
        for (const auto& antenna2: antennas) {
            if (antenna1 == antenna2) {
                continue;
            }
            if (std::get<2>(antenna1) != std::get<2>(antenna2)) {
                continue;
            }
            
            int antenna1_y = std::get<0>(antenna1);
            int antenna1_x = std::get<1>(antenna1);
            int antenna2_y = std::get<0>(antenna2);
            int antenna2_x = std::get<1>(antenna2);
            
            
            int i=0;
            while (true) {
                auto dy = antenna2_y - antenna1_y;
                auto dx = antenna2_x - antenna1_x;
                
                auto antinode_y = antenna1_y - i*dy;
                auto antinode_x = antenna1_x - i*dx;

                if (bound_check(map, antinode_y, antinode_x)) {
                    antinodes.insert(std::make_pair(antinode_y, antinode_x));
                }
                else {
                    break;
                }
                i++;
            }

        }
    }

    for (const auto& antinode: antinodes) {
        std::cout << "Antinode at (" << antinode.first << ", " << antinode.second << ")" << std::endl;
    }


    for (const auto& row: map) {
        for (const auto& cell: row) {
            if (antinodes.find(std::make_pair(&row - &map[0], &cell - &row[0])) != antinodes.end()) {
                std::cout << "#";
            }
            else {
                std::cout << cell;
            }
        }

        std::cout << std::endl;
    }

    std::cout << antinodes.size() << std::endl;
    return 0;
}
