use std::cmp::Ordering;
use std::collections::BinaryHeap;
use std::collections::HashMap;
use std::env;
use std::fs;
use rayon::prelude::*;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn next(map: &Vec<Vec<i32>>, pos: (i32, i32), bounds: (i32, i32)) -> Vec<(i32, i32)> {
    let height = map[pos.0 as usize][pos.1 as usize];

    let mut ns: Vec<(i32, i32)> = Vec::new();
    let left = (pos.0, pos.1 - 1);
    let right = (pos.0, pos.1 + 1);
    let down = (pos.0 - 1, pos.1);
    let up = (pos.0 + 1, pos.1);

    if (right.0 >= 0 && right.0 < bounds.0 && right.1 >= 0 && right.1 < bounds.1)
        && (map[right.0 as usize][right.1 as usize] - height) <= 1
    {
        ns.push(right);
    }
    if (left.0 >= 0 && left.0 < bounds.0 && left.1 >= 0 && left.1 < bounds.1)
        && (map[left.0 as usize][left.1 as usize] - height) <= 1
    {
        ns.push(left);
    }
    if (down.0 >= 0 && down.0 < bounds.0 && down.1 >= 0 && down.1 < bounds.1)
        && (map[down.0 as usize][down.1 as usize] - height) <= 1
    {
        ns.push(down);
    }
    if (up.0 >= 0 && up.0 < bounds.0 && up.1 >= 0 && up.1 < bounds.1)
        && (map[up.0 as usize][up.1 as usize] - height) <= 1
    {
        ns.push(up);
    }

    return ns;
}

fn dijkstra(map: &Vec<Vec<i32>>, start: (i32, i32), end: (i32, i32)) -> Option<i32> {
    let bounds = (map.len() as i32, map[0].len() as i32);
    let mut costs: HashMap<(i32, i32), i32> = HashMap::new();

    for (i, row) in map.iter().enumerate() {
        for (j, _) in row.iter().enumerate() {
            costs.insert((i as i32, j as i32), i32::MAX as i32);
        }
    }
    let mut queue: BinaryHeap<Node> = BinaryHeap::new();

    *costs.get_mut(&start).unwrap() = 0;
    queue.push(Node {
        x: start.0,
        y: start.1,
        previous: None,
        cost: 0,
    });
    loop {
        let node = queue.pop();
        if node.is_none() {
            break;
        }
        let node = node.unwrap();

        if (node.x, node.y) == end {
            return Some(node.cost);
        }

        if node.cost > costs[&(node.x, node.y)] {
            continue;
        }

        for edge in next(map, (node.x, node.y), bounds) {
            let next = Node {
                cost: node.cost + 1,
                x: edge.0,
                y: edge.1,
                previous: Some((node.x, node.y)),
            };
            if next.cost < costs[&(next.x, next.y)] {
                queue.push(next.clone());
                *costs.get_mut(&(next.x, next.y)).unwrap() = next.cost;
            }
        }
    }

    None
}

#[derive(Debug, Clone, Eq, PartialEq)]
struct Node {
    x: i32,
    y: i32,
    previous: Option<(i32, i32)>,
    cost: i32,
}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        other.cost.cmp(&self.cost)
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let mut map: Vec<Vec<i32>> = Vec::new();

    let mut end: (i32, i32) = (0, 0);

    for (i, line) in input.lines().enumerate() {
        map.push(Vec::new());
        for (j, char) in line.chars().enumerate() {
            if char == 'S' {
                map[i].push(0);
            } else if char == 'E' {
                end = (i as i32, j as i32);
                map[i].push('z' as i32 - 'a' as i32);
            } else {
                map[i].push(char as i32 - 'a' as i32);
            }
        }
    }

    let mut starts: Vec<(i32, i32)> = Vec::new();
    for (i, row) in map.iter().enumerate() {
        for (j, _) in row.iter().enumerate() {
            if map[i][j] == 0 {
                starts.push((i as i32, j as i32));
            }
        }
    }

    println!(
        "{}",
        starts
            .par_iter()
            .map(|start| { dijkstra(&map, *start, end).unwrap_or(1000000)})
            .min().unwrap()
    );
}
