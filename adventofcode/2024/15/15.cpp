#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include "data.h"

using Map = std::vector<std::vector<char>>;

struct Input {
    Map map;
    std::vector<char> moves;
};


void print_map(const Map& map) {
    for (const auto& row : map) {
        for (const auto& c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

std::pair<int, int> apply_direction(int y, int x, int direction) {
    if (direction == 0) {
        return {y-1, x};
    }
    else if (direction == 1) {
        return {y, x+1};
    }
    else if (direction == 2) {
        return {y+1, x};
    }
    else if (direction == 3) {
        return {y, x-1};
    }

    throw std::runtime_error("Invalid direction");
}

bool move_boxes(Map& map, int y, int x, int direction) {
    std::pair<int, int> new_pos = apply_direction(y, x, direction);
    bool available = false;
    if (map[y][x] == 'O') {
        available = move_boxes(map, new_pos.first, new_pos.second, direction);
    }
    else if (map[y][x]  == '#') {
        return false;
    }
    else {
        return true;
    }

    if (available) {
        map[new_pos.first][new_pos.second] = map[y][x];
        return true;
    }
    else {
        return false;
    }
}

std::pair<int, int> make_move(Map& map, char move, int y, int x) {
    int target_y = 0;
    int target_x = 0;
    int direction = 0;

    if (move == '>') {
        target_y = y;
        target_x = x + 1;
        direction = 1;
    } 
    else if (move == 'v') {
        target_y = y + 1;
        target_x = x;
        direction = 2;
    }
    else if (move == '<') {
        target_y = y;
        target_x = x - 1;
        direction = 3;
    } 
    else if (move == '^') {
        target_y = y - 1;
        target_x = x;
        direction = 0;
    } 

    auto available = move_boxes(map, target_y, target_x, direction);
    if (available) {
        auto new_pos = apply_direction(y, x, direction);
        map[new_pos.first][new_pos.second] = '@';
        map[y][x] = '.';

        return {new_pos.first, new_pos.second};
    }
    else {
        return {y, x};
    }
}

int main() {

    std::vector<std::string> example1_input = {
        "########",
        "#..O.O.#",
        "##@.O..#",
        "#...O..#",
        "#.#.O..#",
        "#...O..#",
        "#......#",
        "########"
    };

    std::string example1_moves = "<^^>>>vv<v>>v<<";
    
    std::vector<std::string> example2_input = {
        "##########",
        "#..O..O.O#",
        "#......O.#",
        "#.OO..O.O#",
        "#..O@..O.#",
        "#O#..O...#",
        "#O..O..O.#",
        "#.OO.O.OO#",
        "#....O...#",
        "##########"
    };

    std::string example2_moves = \
        "<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^" \
        "vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v" \
        "><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<" \
        "<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^" \
        "^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><" \
        "^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^" \
        ">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^" \
        "<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>" \
        "^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>" \
        "v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^";

    
    auto map = data_input;
    auto moves = data_moves;

    Input input{};
    for (const auto& line : map) {
        std::vector<char> row;
        for (const auto& c : line) {
            row.push_back(c);
        }
        input.map.push_back(row);
    }

    input.moves = std::vector<char>(moves.begin(), moves.end());

    
    int initial_x = 0;
    int initial_y = 0;
    for (int i=0; i< map.size(); i++) {
        for (int j=0; j< map[i].size(); j++) {
            if (input.map[i][j] == '@') {
                initial_x = j;
                initial_y = i;
            }
        }
    }
    

    auto pos = std::make_pair(initial_y, initial_x);
    for (auto move: input.moves) {
        std::cout << std::endl << "Move " << move << std::endl;
        pos = make_move(input.map, move, pos.first, pos.second);
        print_map(input.map);
    }
    
    int acc = 0;
    for (int i=0; i< map.size(); i++) {
        for (int j=0; j< map[i].size(); j++) {
            if (input.map[i][j] == 'O') {
                acc += 100*i + j;
            }
        }
    }

    std::cout << "acc: " << acc << std::endl;


}
