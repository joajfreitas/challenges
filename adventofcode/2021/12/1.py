import sys
from pprint import pprint


def parse_edge(graph, line):
    line = line.strip()
    start, end = line.split("-")

    if start not in graph.keys():
        graph[start] = []

    if end not in graph.keys():
        graph[end] = []

    if end not in graph[start]:
        graph[start].append(end)

    if start not in graph[end]:
        graph[end].append(start)


def search(graph):
    def search_closure(graph, start, path, visited):
        if start == "end":
            return [path]

        paths = []
        ns = graph[start]
        ns = [n for n in ns if n not in visited]
        for n in ns:
            if n == n.upper():
                paths += search_closure(graph, n, path + [n], visited)
            else:
                paths += search_closure(graph, n, path + [n], visited + [n])

        return paths

    return search_closure(graph, "start", ["start"], ["start"])


with open(sys.argv[1]) as f:
    lines = f.readlines()

graph = {}

for line in lines:
    parse_edge(graph, line)


paths = search(graph)
print(len(paths))
