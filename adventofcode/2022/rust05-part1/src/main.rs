use lazy_static::lazy_static;
use regex;
use regex::Regex;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn read_move(line: &str) -> (u32, u32, u32) {
    lazy_static! {
        static ref MOVE_RE: Regex = Regex::new(r"move (\d+) from (\d+) to (\d+)").unwrap();
    }
    let captures = MOVE_RE.captures(line).unwrap();
    let quantity = captures.get(1).unwrap().as_str().parse::<u32>().unwrap();
    let source = captures.get(2).unwrap().as_str().parse::<u32>().unwrap();
    let dest = captures.get(3).unwrap().as_str().parse::<u32>().unwrap();

    (quantity, source, dest)
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());
    let mut stacks: Vec<Vec<char>> = Vec::new();

    for line in input.lines() {
        let chars = line.chars().collect::<Vec<char>>();
        if chars.len() == 0 {
            continue;
        } else if chars[0] == 'm' {
            let (quantity, source, dest) = read_move(line);
            for _i in 0..quantity {
                let value = stacks[(source - 1) as usize].pop().unwrap();
                stacks[(dest - 1) as usize].push(value.clone());
            }
        } else {
            stacks.push(line.chars().collect::<Vec<char>>());
        }
    }

    for stack in stacks {
        print!("{}", stack.last().unwrap());
    }
    print!("\n");
}
