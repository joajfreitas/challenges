use regex;
use std::fs;
use std::env;
use std::collections::HashMap;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[derive(Debug)]
struct Node {
    id : usize,
    name: String,
    edges: Vec<usize>,
    flow: i32,
}

impl Node {
    fn new(id: usize, name: String, edges: Vec<usize>, flow: i32) -> Node {
        Node {
            id,
            name,
            edges,
            flow
        }
    }
}

fn floyd_warshall(graph: &Vec<Node>) -> Vec<Vec<usize>> {
    let mut dists: Vec<Vec<usize>> = Vec::new();

    for i in 0..graph.len() {
        dists.push(Vec::new());
        for _ in 0..graph.len() {
            dists[i].push(10000);
        }
    }

    for (i, vertex) in graph.iter().enumerate() {
        dists[i][i] = 0;
        for edge in &vertex.edges {
            dists[vertex.id][*edge] = 1;
        }
    }
    

    for k in 0..graph.len() {
        for i in 0..graph.len() {
            for j in 0..graph.len() {
                if dists[i][j] > dists[i][k] + dists[k][j] {
                    dists[i][j] = dists[i][k] + dists[k][j];
                }
            }
        }
    }

    dists
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    let re = regex::Regex::new(r"Valve ([A-Z]+) has flow rate=(\d+); tunnels? leads? to valves?(( [A-Z]+,?)+)").unwrap();

    let mut graph : Vec<Node> = Vec::new();
    let mut node_mapping: HashMap<String, usize> = HashMap::new();

    for capture in re.captures_iter(&input) {
        let valve = capture.get(1).unwrap().as_str();
        let flow = capture.get(2).unwrap().as_str().parse::<i32>().unwrap();
        
        node_mapping.insert(valve.to_string(), graph.len());
        graph.push(Node::new(graph.len(),valve.to_string(), vec![], flow));
    }

    for (node, capture) in re.captures_iter(&input).enumerate() {
        let connecting_valve = capture.get(3).unwrap().as_str();
        let connecting_valve = connecting_valve.split(", ").map(|x| node_mapping[&x.trim().to_string()]).collect::<Vec<usize>>();

        graph[node].edges = connecting_valve;
    }

    println!("{:?}", graph);
    println!("{:?}", floyd_warshall(&graph));
}
