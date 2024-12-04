#include <iostream>
#include "data.h"

char get_char(const std::vector<std::vector<char>>& map, int row, int col) {
    if (row < 0 || col < 0) {
        return 'Z';
    }

    if (row >= static_cast<int>(map.size()) || col >= static_cast<int>(map[0].size())) {
        return 'Z';
    }

    return map[row][col];
}


int search_beam(const std::vector<std::vector<char>>& map, int row, int col, int row_v, int row_c) {
    static std::string search_string = "XMAS";

    bool found = true;
    for (int i=0; i<static_cast<int>(search_string.size()); i++) {
        if (get_char(map, row + row_v*i, col + row_c*i) != search_string[i]) {
            found = false;
            break;
        }
    }   

    return found;
}

int search(const std::vector<std::vector<char>>& map, int row, int col) {
    static std::string search_string = "XMAS";

    int acc = 0;

    acc += search_beam(map, row, col, 1, 0);
    acc += search_beam(map, row, col, 0, 1);
    acc += search_beam(map, row, col,-1, 0);
    acc += search_beam(map, row, col, 0,-1);
    acc += search_beam(map, row, col,-1,-1);
    acc += search_beam(map, row, col,-1, 1);
    acc += search_beam(map, row, col, 1,-1);
    acc += search_beam(map, row, col, 1, 1);

    return acc;
}


bool search2(const std::vector<std::vector<char>>& map, int row, int col) {
    static std::string search_string = "MAS";

    char top_left = get_char(map, row-1, col-1);
    char top_right = get_char(map, row-1, col+1);
    char bottom_left = get_char(map, row+1, col-1);
    char bottom_right = get_char(map, row+1, col+1);

    return ((top_left == 'M' && bottom_right == 'S') || (top_left == 'S' && bottom_right == 'M')) &&     ((top_right == 'M' && bottom_left == 'S') || (top_right == 'S' && bottom_left == 'M'));
}


int main() {
    int acc = 0;
    for (int row = 0; row < static_cast<int>(data.size()); row++) {
        for (int col = 0; col < static_cast<int>(data[0].size()); col++) {
            char c = get_char(data, row, col);
            if (c == 'X') {
                int found =  search(data, row, col);
                acc += found;
            }
        }
    }

    std::cout << "acc: " << acc << std::endl;

    
    acc = 0;
    for (int row = 0; row < static_cast<int>(data.size()); row++) {
        for (int col = 0; col < static_cast<int>(data[0].size()); col++) {
            char c = get_char(data, row, col);
            if (c == 'A') {
                acc += search2(data, row, col);
            }
        }
    }


    std::cout << "acc: " << acc << std::endl;
    return 0;
}
