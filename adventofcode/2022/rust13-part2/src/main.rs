use std::cmp::Ordering;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[derive(Debug, Clone, Eq, PartialEq)]
enum Node {
    List(Vec<Node>),
    Int(i32),
}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        match (self, other) {
            (Node::List(l1), Node::List(l2)) => {
                for (e1, e2) in l1.iter().zip(l2) {
                    let r = e1.cmp(e2);
                    if r.is_eq() {
                        continue;
                    } else {
                        return r;
                    }
                }

                l1.len().cmp(&l2.len())
            }
            (Node::Int(i1), Node::Int(i2)) => i1.cmp(i2),
            (Node::List(_), Node::Int(_)) => self.cmp(&Node::List(vec![other.clone()])),
            (Node::Int(_), Node::List(_)) => Node::List(vec![self.clone()]).cmp(other),
        }
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Node {
    fn parse(line: &mut Vec<String>) -> Node {
        let c = line.pop().unwrap();
        if c == "[" {
            Node::List(Node::read_list(line))
        } else {
            Node::read_atom(c)
        }
    }

    fn read_list(line: &mut Vec<String>) -> Vec<Node> {
        let mut nodes: Vec<Node> = Vec::new();
        loop {
            let token = &line[line.len() - 1];
            if token == "]" {
                line.pop();
                return nodes;
            }

            nodes.push(Node::parse(line));
        }
    }

    fn read_atom(atom: String) -> Node {
        Node::Int(atom.parse::<i32>().unwrap())
    }
}

fn read_number(chars: Vec<char>) -> (String, Vec<char>) {
    let mut chars = chars.clone();
    let mut number: String = String::new();
    loop {
        let c = chars[chars.len() - 1];
        if !c.is_numeric() {
            break;
        }
        number.push(c);
        chars.pop();
    }
    (number, chars.clone())
}

fn tokenize(line: &str) -> Vec<String> {
    let mut tokens: Vec<String> = Vec::new();

    let mut chars = line.chars().collect::<Vec<char>>();
    chars.reverse();
    loop {
        if chars.len() == 0 {
            break;
        }
        let c = chars[chars.len() - 1];
        if c == '[' {
            chars.pop();
            tokens.push("[".to_string());
        } else if c == ']' {
            chars.pop();
            tokens.push("]".to_string());
        } else if c.is_numeric() {
            let r = read_number(chars.clone());
            tokens.push(r.0);
            chars = r.1;
        } else {
            chars.pop();
            continue;
        }
    }

    tokens
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    let mut nodes = input
        .split("\n")
        .filter(|x| x != &"")
        .map(|packet| {
            let mut tokens = tokenize(packet);
            tokens.reverse();
            Node::parse(&mut tokens)
        })
        .collect::<Vec<Node>>();

    let locator1 = Node::List(vec![Node::List(vec![Node::Int(2)])]);
    nodes.push(locator1.clone());
    let locator2 = Node::List(vec![Node::List(vec![Node::Int(6)])]);
    nodes.push(locator2.clone());
    nodes.sort();

    let mut loc1 = 0;
    let mut loc2 = 0;
    for (i, node) in nodes.iter().enumerate() {
        if *node == locator1 {
            loc1 = i + 1;
        }
        if *node == locator2 {
            loc2 = i + 1;
        }
    }

    println!("{} {} {}", loc1, loc2, loc1 * loc2);
}
