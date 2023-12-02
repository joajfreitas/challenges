use rust_2023::read_aoc_input;
use std::env;

fn parse_line(line: &str) {
    let parts = line.split(":");

    println!("{:?}", parts);
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!("{}", input);
}
