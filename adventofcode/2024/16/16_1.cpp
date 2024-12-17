#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <limits>

#include "data.h"


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

enum Direction {
    North,
    East,
    South,
    West,
};

struct GraphNode {
    int y;
    int x;
    int direction;
    std::vector<int> neighbors;
    
    GraphNode() = default;
    GraphNode(int y, int x, int direction) : y(y), x(x), direction(direction), neighbors{} {neighbors.reserve(6);}

    std::string to_string() const {
        return std::string("Node: x=") + std::to_string(x) + " y=" + std::to_string(y) + " direction=" + std::to_string(direction);
    }
};

using Graph = std::unordered_map<int, GraphNode>;


bool check_in_range(const std::vector<std::string>& map, int y, int x) {
    if (y < 0 || y >= map.size() || x < 0 || x >= map[0].size()) {
        return false;
    }
    return true;
}

char get_map_element(const std::vector<std::string>& map, int y, int x) {
    if (check_in_range(map, y, x)) {
        return map[y][x];
    }
    return '#';
}

std::pair<int, int> apply_move(int y, int x, int direction) {
    if (direction == 0) {
        return { y-1, x};
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

class Hash {
    public:
    Hash(const std::vector<std::string>& map): size_y{map.size()}, size_x{map[0].size()}{}

    int operator()(int y, int x, int direction) const { return 4*(y *size_x + x) + direction; } 

    int size_x;
    int size_y;
};

int wrap_up(int direction) {
    return (direction + 1) % 4;
}

int wrap_down(int direction) {
    return (direction + 5) % 4;
}

void build_graph(Graph& graph, Hash hash, std::vector<std::string> data){
    for (int i=0; i<data.size(); i++) {
        for (int j=0; j<data[i].size(); j++) {
            if (data[i][j] == '#') {
                continue;
            }

            for (int direction=0; direction<4; direction++) {
                GraphNode node = {i, j, direction};
                
                auto neighbor = apply_move(i, j, direction);
                if (get_map_element(data, neighbor.first, neighbor.second) != '#') {
                    node.neighbors.push_back(hash(neighbor.first, neighbor.second, direction));
                }
                node.neighbors.push_back(hash(i,j,wrap_up(direction)));
                node.neighbors.push_back(hash(i,j,wrap_down(direction)));

                graph[hash(node.y, node.x, node.direction)] = node;
            }
        }
    }
}


std::pair<int, int> find_source(const std::vector<std::string>& data) {
    for (int i=0; i<data.size(); i++) {
        for (int j=0; j<data[i].size(); j++) {
            if (data[i][j] == 'S') {
                return {i, j};
            }
        }
    }
    throw std::runtime_error("No source found");
}

std::pair<int, int> find_goal(const std::vector<std::string>& data) {
    for (int i=0; i<data.size(); i++) {
        for (int j=0; j<data[i].size(); j++) {
            if (data[i][j] == 'E') {
                return {i, j};
            }
        }
    }
    throw std::runtime_error("No source found");
}

int edge_cost(const GraphNode& node, const GraphNode& neighbor) {
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

//function Dijkstra(Graph, source):
//     
//      for each vertex v in Graph.Vertices:
//          dist[v] ← INFINITY
//          prev[v] ← UNDEFINED
//          add v to Q
//      dist[source] ← 0
//     
//      while Q is not empty:
//          u ← vertex in Q with minimum dist[u]
//          remove u from Q
//         
//          for each neighbor v of u still in Q:
//              alt ← dist[u] + Graph.Edges(u, v)
//              if alt < dist[v]:
//                  dist[v] ← alt
//                  prev[v] ← u
//
//      return dist[], prev[]


const std::pair<std::vector<int>, std::vector<int>> dijkstra(const Graph& graph, const Hash& hash, std::pair<int, int> source, std::pair<int, int> goal) {

    std::vector<int> dist(318096);
    std::vector<int> prev(318096);
    
    auto cmp = [&dist](int l, int r) { return dist[l] > dist[r]; };
    Queue<int, std::vector<int>, decltype(cmp)> Q{cmp};
    
    auto source_hash = hash(source.first, source.second, East);
    for (const auto& [key, value] : graph) {
        if (source_hash == key) {
            continue;
        }
        dist[key] = 100000000;
        prev[key] = -1;
        Q.push(key);
    }

    dist[source_hash] = 0;
    Q.push(source_hash);

    while (Q.size() != 0) {
        std::make_heap(const_cast<int*>(&Q.top()),
               const_cast<int*>(&Q.top()) + Q.size(),
               cmp);
        auto u = Q.top();
        Q.pop();

        for (const auto& neighbor : graph.at(u).neighbors) {
            if (Q.find(neighbor) == Q.end()) {
                continue;
            }

            auto alt = dist[u] + edge_cost(graph.at(u), graph.at(neighbor));
            if (alt < dist[neighbor]) {
                dist[neighbor] = alt;
                prev[neighbor] = u;
            }
        }
    }

    return {dist, prev};
}

int main(int argc, char* argv[]) {
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

    Graph graph{};
    graph.reserve(44000);
    
    auto data = actual_data;
    auto hash = Hash(data);
    build_graph(graph, hash, data);
    auto source = find_source(data);
    auto goal = find_goal(data);
    auto r = dijkstra(graph, hash, source, goal);

    std::cout << r.first[hash(goal.first, goal.second, North)] << std::endl;
    std::cout << r.second[hash(goal.first, goal.second, North)] << std::endl;
    return 0;
}

