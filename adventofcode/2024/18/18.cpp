#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include <optional>

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

struct GraphNode {
    int y;
    int x;
    int index;
    std::vector<int> neighbors;

    GraphNode(int y, int x, int index): y{y}, x{x}, index{index}, neighbors{} {
        neighbors.reserve(4);
    }

    GraphNode(): GraphNode(0, 0, 0) {}

    std::string to_string() const {
        std::string result = "Node: index=" + std::to_string(index) + " x=" + std::to_string(x) + " y=" + std::to_string(y) + " neighbors=";
        for (const auto& neighbor : neighbors) {
            result += std::to_string(neighbor) + " ";
        }
        return result;
    }
};

struct Graph {
    std::unordered_map<int, GraphNode> nodes;

    std::string to_string() const {
        std::string result = "";
        for (const auto& node : nodes) {
            result += node.second.to_string() + "\n";
        }
        return result;
    }
};

struct Hash {
    Hash(int size_y, int size_x): size_y{size_y}, size_x{size_x} {}

    int operator()(int y, int x) const { return y*size_x + x; }
    int operator()(GraphNode node) const { return node.y*size_x + node.x; }

    int size_y;
    int size_x;
};

Graph build_graph(const std::vector<std::vector<int>>& map, const Hash& hash) {
    Graph graph{};

    int index = 0 ;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j] == 1) {
                continue;
            }

            GraphNode node = {i, j, index++};

            if (i > 0 && map[i-1][j] == 0) {
                node.neighbors.push_back(hash((i-1), j));
            }
            if (j > 0 && map[i][j-1] == 0) {
                node.neighbors.push_back(hash(i, (j-1)));
            }
            if (i < map.size()-1 && map[i+1][j] == 0) {
                node.neighbors.push_back(hash((i+1), j));
            }
            if (j < map[i].size()-1 && map[i][j+1] == 0) {
                node.neighbors.push_back(hash(i, (j+1)));
            }

            graph.nodes[hash(node)]=node;
        }
    }

    return graph;
}


std::optional<std::vector<int>> bfs(Graph& graph, const Hash& hash, std::pair<int, int> source, std::pair<int, int> goal) {
    std::set<int> visited{};
    auto Q = Queue<int, std::vector<int>, std::greater<int>>{};

    std::vector<int> prev{};
    std::vector<int> dist{};
    prev.reserve(graph.nodes.size());

    for (const auto& node : graph.nodes) {
        prev.push_back(-1);
        dist.push_back(100000000);
    }
    
    auto source_node = graph.nodes[hash(source.first, source.second)];
    Q.push(hash(source_node));
    dist[source_node.index] = 0;

    while (Q.size() != 0) {
        auto v = Q.top();
        Q.pop();
        
        auto v_node = graph.nodes[v];
        if (v_node.y == goal.first && v_node.x == goal.second) {
            return prev;
        }
        for (const auto& w : v_node.neighbors) {
            auto w_node = graph.nodes[w];
            if (dist[w_node.index] > dist[v_node.index] + 1) {
                visited.insert(w);
                prev[w_node.index] = v;
                dist[w_node.index] = dist[v_node.index] + 1;
                Q.push(w);
            }
        }
    }
    
    return std::nullopt;
}

int main() {

  std::vector<std::pair<int, int>> example1 = {
      {5, 4}, {4, 2}, {4, 5}, {3, 0}, {2, 1}, {6, 3}, {2, 4}, {1, 5}, {0, 6},
      {3, 3}, {2, 6}, {5, 1}, {1, 2}, {5, 5}, {2, 5}, {6, 5}, {1, 4}, {0, 4},
      {6, 4}, {1, 1}, {6, 1}, {1, 0}, {0, 5}, {1, 6}, {2, 0}};

    
    auto data = actual_data;
    int size_y = 71;
    int size_x = 71;

    std::pair<int, int> source = {0, 0};
    std::pair<int, int> goal = {size_y-1, size_x-1};

    int bytes = 1024;

    auto hash = Hash(size_y, size_x);
    
    for (int bytes_=bytes; bytes_<data.size(); bytes_++) {
        std::vector<std::vector<int>> map{};

        for (int i=0; i<size_y; i++) {
            std::vector<int> row{};
            for (int j=0; j<size_x; j++) {
                row.push_back(0);
            }
            map.push_back(row);
        }

        for (int i=0; i<bytes_; i++) {
            map[data[i].first][data[i].second] = 1;
        }

        Graph graph = build_graph(map, hash);

        auto r = bfs(graph, hash, source, goal);
        if (!r.has_value()) {
            std::cout << data[bytes_-1].first << "," << data[bytes_-1].second << std::endl;
            break;
        }
    }
    return 0;
}
