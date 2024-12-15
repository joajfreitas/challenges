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

bool check_boxes(Map& map, int y, int x, int direction) {
    std::pair<int, int> new_pos = apply_direction(y, x, direction);

    if ((direction == 1 || direction == 3) && (map[y][x] == ']' || map[y][x] == '[')) {
        return check_boxes(map, new_pos.first, new_pos.second, direction);
    }
    else if ((direction == 0 || direction == 2) && map[y][x] == ']') {
        auto available = check_boxes(map, new_pos.first, new_pos.second, direction);
        return available && check_boxes(map, new_pos.first, new_pos.second-1, direction);
    }
    else if ((direction == 0 || direction == 2) && map[y][x] == '[') {
        auto available = check_boxes(map, new_pos.first, new_pos.second, direction);
        return available && check_boxes(map, new_pos.first, new_pos.second+1, direction);
    }
    else if (map[y][x]  == '#') {
        return false;
    }
    else {
        return true;
    }

}

std::pair<bool,int> move_boxes(Map& map, int y, int x, int direction) {
    std::pair<int, int> new_pos = apply_direction(y, x, direction);
    bool available = true;

    int width = 0;
    if ((direction == 1 || direction == 3) && (map[y][x] == ']' || map[y][x] == '[')) {
        auto available_ = move_boxes(map, new_pos.first, new_pos.second, direction);
        available = available_.first;
    }
    else if ((direction == 0 || direction == 2) && map[y][x] == ']') {
        auto available_ = move_boxes(map, new_pos.first, new_pos.second, direction);
        available = available && available_.first;
        available_ = move_boxes(map, new_pos.first, new_pos.second-1, direction);
        available = available && available_.first;
        width = -1;
    }
    else if ((direction == 0 || direction == 2) && map[y][x] == '[') {
        auto available_ = move_boxes(map, new_pos.first, new_pos.second, direction);
        available = available && available_.first;
        available_ = move_boxes(map, new_pos.first, new_pos.second+1, direction);
        available = available && available_.first;
        width = 1;
    }
    else if (map[y][x]  == '#') {
        return {false, 0};
    }
    else {
        return {true, 0};
    }

    if (available) {
        map[new_pos.first][new_pos.second] = map[y][x];
        if (width != 0) {
            map[new_pos.first][new_pos.second+width] = map[y][x+width];
            map[y][x+width] = '.';
        }
        return {true, width};
    }
    else {
        return {false, 0};
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
    else {
        throw std::runtime_error("Invalid move");
    }
    
    std::cout << "direction: " << direction << std::endl;

    auto to_move = check_boxes(map, target_y, target_x, direction);
    if (to_move) {
        auto [available, width] = move_boxes(map, target_y, target_x, direction);
        std::cout << "available" << std::endl;

        std::cout << "y: " << y << " x: " << x << std::endl;
        auto new_pos = apply_direction(y, x, direction);
        map[new_pos.first][new_pos.second] = '@';
        if (width != 0) {
            //map[y][x+width] = '.';
        }
        std::cout << "new y: " << new_pos.first << " new x: " << new_pos.second << std::endl;
        map[y][x] = '.';

        return {new_pos.first, new_pos.second};
    }
    else {
        std::cout << "not available" << std::endl;
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

    std::vector<std::string> example3_input = {
        "#######",
        "#...#.#",
        "#.....#",
        "#..OO@#",
        "#..O..#",
        "#.....#",
        "#######"
    };

    std::string example3_moves = "<vv<<^^<<^^";
    
    auto map = data_input;
    auto moves = data_moves;

    Input input{};
    for (const auto& line : map) {
        std::vector<char> row;
        for (const auto& c : line) {
            if (c == 'O') {
                row.push_back('[');
                row.push_back(']');
            }
            else if (c == '@') {
                row.push_back('@');
                row.push_back('.');
            }
            else {
                row.push_back(c);
                row.push_back(c);
            }
        }
        input.map.push_back(row);
    }

    input.moves = std::vector<char>(moves.begin(), moves.end());

    print_map(input.map);

    int initial_x = 0;
    int initial_y = 0;
    for (int i=0; i< map.size(); i++) {
        for (int j=0; j< input.map[i].size(); j++) {
            if (input.map[i][j] == '@') {
                initial_x = j;
                initial_y = i;
            }
        }
    }

    std::cout << "initial x: " << initial_x << " initial y: " << initial_y << std::endl;
    

    auto pos = std::make_pair(initial_y, initial_x);
    for (auto move: input.moves) {
        std::cout << std::endl << "Move " << move << std::endl;
        pos = make_move(input.map, move, pos.first, pos.second);
        print_map(input.map);
    }
    
    int acc = 0;
    for (int i=0; i< input.map.size(); i++) {
        for (int j=0; j< input.map[i].size(); j++) {
            if (input.map[i][j] == '[') {
                auto v = 100*i + j;
                std::cout << "v: " << v << std::endl;
                acc += v;
            }
        }
    }

    std::cout << "acc: " << acc << std::endl;


}
