#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <optional>
#include <limits>
#include <algorithm>

#include  "data.h"

template<
    class T,
    class Container,
    class Compare
> class Queue : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename
        std::priority_queue<
        T,
        Container,
        Compare>::container_type::const_iterator const_iterator;

    typedef typename
        std::priority_queue<
        T,
        Container,
        Compare>::container_type::iterator iterator;

     using std::priority_queue<T, Container, Compare>::priority_queue;

    const_iterator find(const T&val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return first;
            ++first;
        }
        return last;
    }

    iterator begin() {
        return this->c.begin();
    }

    iterator end() {
        return this->c.begin();
    }

    const_iterator begin() const {
        return this->c.begin();
    }

    const_iterator end() const {
        return this->c.begin();
    }


    
};


enum {
    North = 0,
    East = 1,
    South = 2,
    West = 3
} Direction;

std::string direction_to_string(int direction) {
    switch (direction) {
        case North:
            return "North";
        case East:
            return "East";
        case South:
            return "South";
        case West:
            return "West";
        default:
            return "Unknown";
    }
}

struct Map {
    int initial_x{};
    int initial_y{};
    int goal_x{};
    int goal_y{};
    std::vector<std::vector<char>> map{};
    
    bool in_range(int y, int x) const {
        return y >= 0 && y < map.size() && x >= 0 && x < map[0].size();
    }

    char get(int y, int x) const {
        if (in_range(y, x)) {
            return map[y][x];
        }
        else {
            return '#';
        }
    }
};

struct Node {
    int x;
    int y;
    int direction;
    int cost;

    bool operator==(const Node& rhs) const
  {
      return x == rhs.x && y == rhs.y && direction == rhs.direction;
  }

    std::string to_string() const {
        return std::string("Node: x=") + std::to_string(x) + " y=" + std::to_string(y) + " direction=" + direction_to_string(direction);
    }
};

struct {
    bool operator()(const Node l, const Node r) const { return l.cost > r.cost; }
} NodeComparator;

int heuristic(const Map& map, const Node& node) {
    //if (map.goal_x == node.x && map.goal_y > node.y) { 
    //    if (node.direction == South) {
    //        return abs(map.goal_x - node.x) + abs(map.goal_y - node.y);
    //    }
    //    else if (node.direction == North) {
    //        return abs(map.goal_x - node.x) + abs(map.goal_y - node.y) + 2000;
    //    }
    //    else {
    //        return abs(map.goal_x - node.x) + abs(map.goal_y - node.y) + 1000;
    //    }
    //    return abs(map.goal_x - node.x) + abs(map.goal_y - node.y) + 1000;
    //}
    //else  {
    //    return abs(map.goal_x - node.x) + abs(map.goal_y - node.y);
    //}
    //return 0;
    
    return abs(map.goal_x - node.x) + abs(map.goal_y - node.y);
}

int to_index(const Map& map, int y, int x, int direction) {
    return direction * map.map.size() * map.map[0].size() + map.map[0].size() * y + x;
}

int to_index(const Map& map, const Node& node) {
    return to_index(map, node.y , node.x, node.direction);;
}
//function reconstruct_path(cameFrom, current)
//    total_path := {current}
//    while current in cameFrom.Keys:
//        current := cameFrom[current]
//        total_path.prepend(current)
//    return total_path

std::vector<Node> reconstruct_path(const Map& map, const std::map<int, Node>& came_from, const Node& current) {
    std::vector<Node> total_path{};
    total_path.push_back(current);
    
    auto current_ = current;
    while (came_from.find(to_index(map, current_)) != came_from.end()) {
        current_ = came_from.at(to_index(map, current_));
        total_path.push_back(current_);
    }

    return total_path;
}

int wrap_up(int x) {
    return (x + 1) % 4;
}

int wrap_down(int x) {
    if (x == 0) {
        return 3;
    }
    else {
        return x - 1;
    }
}

std::vector<Node> neighbors(const Map& map, const Node& node) {
    std::vector<Node> neighbors{};
    
    if (node.direction == North && map.get(node.y - 1, node.x) != '#') {
        neighbors.push_back({node.x, node.y - 1, node.direction, 0});
    }
    else if (node.direction == East && map.get(node.y, node.x+1) != '#') {
        neighbors.push_back({node.x+1, node.y, node.direction, 0});
    }
    else if (node.direction == South && map.get(node.y+1, node.x) != '#') {
        neighbors.push_back({node.x, node.y+1, node.direction, 0});
    }
    else if (node.direction == West && map.get(node.y, node.x-1) != '#') {
        neighbors.push_back({node.x-1, node.y, node.direction, 0});
    }

    neighbors.push_back({node.x, node.y, wrap_up(node.direction), 0});
    neighbors.push_back({node.x, node.y, wrap_down(node.direction), 0});
    return neighbors;
}

int edge_weight(const Map& map, const Node& node, const Node& neighbor) {
    if (node.x == neighbor.x && node.y == neighbor.y) {
        if (wrap_up(node.direction) == neighbor.direction) {
            return 1000;
        }
        else if (wrap_down(node.direction)  == neighbor.direction) {
            return 1000;
        }
    }
    else if (node.direction == neighbor.direction && std::abs(node.x - neighbor.x) + std::abs(node.y - neighbor.y) == 1) {
        return 1;
    }
    else {
        return std::numeric_limits<int>::max();
    }
}

unsigned map_get(std::map<int, unsigned> map, int key) {
    if (map.find(key) != map.end()) {
        return map.at(key);
    }
    else {
        return 100000000; 
    }   
}

std::optional<std::vector<std::vector<Node>>> search(const Map& map) {
    auto cmp = [](Node l, Node r) { return l.cost > r.cost; };
    Queue<Node, std::vector<Node>, decltype(cmp)> open_list(cmp);

    open_list.push({map.initial_x, map.initial_y, East, 0});

    //std::cout << "open list size: " << open_list.size() << std::endl;

    std::map<int, Node> came_from{};
    std::map<int, unsigned> gscore{};
    gscore[to_index(map, open_list.top())] = 0;

    gscore[to_index(map, open_list.top())] = 0;

    std::map<int, unsigned> fscore{};
    fscore[to_index(map, open_list.top())] = heuristic(map, open_list.top());



    //std::cout << "open list size: " << open_list.size() << std::endl;

    while (!open_list.empty()) {
        //std::cout << "iter" << std::endl;
        //current := the node in openSet having the lowest fScore[] value
        auto current = open_list.top();

        //std::cout << "current: " << current.to_string() << std::endl;
        //if current = goal
        //    return reconstruct_path(cameFrom, current)
        //if (current.x == map.goal_x && current.y == map.goal_y) {
        //    return reconstruct_path(map, came_from, current);
        //}
        
        //openSet.Remove(current)
        open_list.pop();

        auto neighbors_ = neighbors(map, current);

        //std::cout << "neighbors size: " << neighbors_.size() << std::endl;

        //for each neighbor of current
        for (auto neighbor : neighbors_) {
             //std::cout << "neighbor: " << neighbor.to_string() << std::endl;
        //    // d(current,neighbor) is the weight of the edge from current to neighbor
        //    // tentative_gScore is the distance from start to the neighbor through current
        //    tentative_gScore := gScore[current] + d(current, neighbor)
              auto tentative_gscore = map_get(gscore,to_index(map, current)) + edge_weight(map, current, neighbor);
        //    if tentative_gScore < gScore[neighbor]
              //std::cout << "tentative_gscore: " << tentative_gscore << std::endl;
               auto neigbor_weight = map_get(gscore,to_index(map, neighbor));
               //std::cout << "neighor weight: " << neigbor_weight << std::endl;
              if (tentative_gscore < neigbor_weight) {
        //        // This path to neighbor is better than any previous one. Record it!
        //        cameFrom[neighbor] := current
                  came_from[to_index(map, neighbor)] = current; 
        //        gScore[neighbor] := tentative_gScore
                  gscore[to_index(map, neighbor)] = tentative_gscore;   
        //        fScore[neighbor] := tentative_gScore + h(neighbor)
                  fscore[to_index(map, neighbor)] = tentative_gscore + heuristic(map, neighbor); 
        //        if neighbor not in openSet
                  if  (std::find(open_list.begin(), open_list.end(), neighbor) == open_list.end()) {
        //            openSet.add(neighbor)
                      open_list.push(neighbor);
                      //std::cout << "neighbor added to open list" << std::endl;
                  }
                  else {
                      //std::cout << "neighbor already in open list" << std::endl;
                  }
              }
        }


        //std::cout << "open list size: " << open_list.size() << std::endl;
    }
    
    return std::vector<std::vector<Node>>{
        reconstruct_path(map, came_from, Node{map.goal_x, map.goal_y, 0, 0}),
        reconstruct_path(map, came_from, Node{map.goal_x, map.goal_y, 1, 0}),
        reconstruct_path(map, came_from, Node{map.goal_x, map.goal_y, 2, 0}),
        reconstruct_path(map, came_from, Node{map.goal_x, map.goal_y, 3, 0}),
    }
        ;
}

int main() {
    std::vector<std::string> example1 = {
        "###############",
        "#.......#....E#",
        "#.#.###.#.###.#",
        "#.....#.#...#.#",
        "#.###.#####.#.#",
        "#.#.#.......#.#",
        "#.#.#####.###.#",
        "#...........#.#",
        "###.#.#####.#.#",
        "#...#.....#.#.#",
        "#.#.#.###.#.#.#",
        "#.....#...#.#.#",
        "#.###.#.#.#.#.#",
        "#S..#.....#...#",
        "###############"
    };
    //     012345678901234
    //  0 "###############",
    //  1 "#.......#....E#",
    //  2 "#.#.###.#.###.#",
    //  3 "#.....#.#...#.#",
    //  4 "#.###.#####.#.#",
    //  5 "#.#.#.......#.#",
    //  6 "#.#.#####.###.#",
    //  7 "#...........#.#",
    //  8 "###.#.#####.#.#",
    //  9 "#...#.....#.#.#",
    // 10 "#.#.#.###.#.#.#",
    // 11 "#.....#...#.#.#",
    // 12 "#.###.#.#.#.#.#",
    // 13 "#S..#.....#...#",
    // 14 "###############"
   

    std::vector<std::string> example2 = {
        "#################",
        "#...#...#...#..E#",
        "#.#.#.#.#.#.#.#.#",
        "#.#.#.#...#...#.#",
        "#.#.#.#.###.#.#.#",
        "#...#.#.#.....#.#",
        "#.#.#.#.#.#####.#",
        "#.#...#.#.#.....#",
        "#.#.#####.#.###.#",
        "#.#.#.......#...#",
        "#.#.###.#####.###",
        "#.#.#...#.....#.#",
        "#.#.#.#####.###.#",
        "#.#.#.........#.#",
        "#.#.#.#########.#",
        "#S#.............#",
        "#################"
    };

    auto data = actual_data;
    Map map{};
    
    for (int i=0; i<data.size(); i++) {
        std::vector<char> row{};
        for (int j=0; j<data[i].size(); j++) {
            row.push_back(data[i][j]);

            if (data[i][j] == 'S') {
                map.initial_x = j;
                map.initial_y = i;
            }
            if (data[i][j] == 'E') {
                map.goal_x = j;
                map.goal_y = i;
            }
        }
        map.map.push_back(row);
    }

    auto path = search(map).value();
    
    for (int j=0; j<4; j++) {
        int acc = 0;
        for (int i=path[j].size()-1; i>0; i--) {
            //std::cout << path[j][i].to_string() << std::endl;  
            acc += edge_weight(map, path[j][i], path[j][i-1]);
        }
        std::cout << "Acc: " << acc << std::endl;
    }


}
