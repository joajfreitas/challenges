use regex;
use std::env;
use std::fs;
use vec_tree::{Index, VecTree};

#[derive(Debug)]
enum INode {
    Dir(String),
    File((String, i32)),
}

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[allow(dead_code)]
fn print_tree(tree: &VecTree<INode>, node: Index, separator: &String) {
    let separator = separator.clone() + "-";
    for children in tree.children(node) {
        print_tree(tree, children, &separator);
    }
}

fn find_children(tree: &VecTree<INode>, node: Index, root: Index, name: &str) -> Option<Index> {
    if name == ".." {
        return tree.parent(node);
    } else if name == "/" {
        return Some(root);
    }
    for children in tree.children(node) {
        match tree.get(children).unwrap() {
            INode::Dir(dirname) => {
                if dirname == name {
                    return Some(children);
                }
            }
            _ => {}
        }
    }

    None
}

fn find_dirs(tree: &VecTree<INode>, node: Index, dirs: &mut Vec<(String, i32)>) -> i32 {
    let mut acc = 0;
    for children in tree.children(node) {
        let child = tree.get(children).unwrap();
        match child {
            INode::Dir(_) => {
                acc += find_dirs(tree, children, dirs);
            }
            INode::File((_, size)) => {
                acc += size;
            }
        };
    }

    if acc <= 100000 {
        match tree.get(node).unwrap() {
            INode::Dir(name) => {
                dirs.push((name.clone(), acc));
            }
            _ => panic!(),
        }
    }
    acc
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let command_re = regex::Regex::new(r"\$ ([a-z]+)\s?([[\.]|[a-z]|[/]]*)").unwrap();
    let file_re = regex::Regex::new(r"([0-9]+) ([a-z|\.]+)").unwrap();
    let dir_re = regex::Regex::new(r"dir ([a-z|\.]+)").unwrap();

    let mut tree = VecTree::new();

    let root = tree.insert_root(INode::Dir("/".to_string()));
    let mut cwd = root;

    for line in input.lines().skip(1) {
        if command_re.is_match(line) {
            let captures = command_re.captures(line).unwrap();
            match captures.get(1).unwrap().as_str() {
                "cd" => {
                    let dirname = captures.get(2).unwrap().as_str();
                    cwd = find_children(&tree, cwd, root, dirname).unwrap();
                }
                "ls" => {}
                _ => panic!(),
            };
        }
        if file_re.is_match(line) {
            let file_size = file_re
                .captures(line)
                .unwrap()
                .get(1)
                .unwrap()
                .as_str()
                .parse::<i32>()
                .unwrap();
            let file = file_re.captures(line).unwrap().get(2).unwrap().as_str();
            tree.insert(INode::File((file.to_string(), file_size)), cwd);
        } else if dir_re.is_match(line) {
            let dir_name = dir_re.captures(line).unwrap().get(1).unwrap().as_str();
            tree.insert(INode::Dir(dir_name.to_string()), cwd);
        }
    }

    let mut dirs: Vec<(String, i32)> = Vec::new();
    find_dirs(&tree, root, &mut dirs);
    println!("{:?}", dirs.iter().map(|x| x.1).sum::<i32>());
}
