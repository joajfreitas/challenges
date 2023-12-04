use rust_2023::read_aoc_input;
use std::env;

use std::collections::HashSet;

use regex::Regex;

fn parse_input(line: &str) -> (u32, HashSet<u32>, HashSet<u32>) {
    let line_re = Regex::new(r"Card +(\d+):(.+)\|(.+)").unwrap();
    let number_re = Regex::new(r" +(\d+)").unwrap();

    let caps = line_re.captures(line).unwrap();

    let card_number = caps.get(1).unwrap().as_str().parse::<u32>().unwrap();
    let winning_numbers = caps.get(2).unwrap().as_str();
    let your_numbers = caps.get(3).unwrap().as_str();

    let winning_numbers: HashSet<u32> = number_re
        .captures_iter(winning_numbers)
        .map(|cap| cap.get(1).unwrap().as_str().parse::<u32>().unwrap())
        .collect();
    let your_numbers: HashSet<u32> = number_re
        .captures_iter(your_numbers)
        .map(|cap| cap.get(1).unwrap().as_str().parse::<u32>().unwrap())
        .collect();

    (card_number, winning_numbers, your_numbers)
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!(
        "{:?}",
        input
            .lines()
            .map(parse_input)
            .map(|line| {
                let len = line
                    .1
                    .intersection(&line.2)
                    .map(|x| *x)
                    .collect::<HashSet<u32>>()
                    .len();
                if len == 0 {
                    0
                } else {
                    2_i32.pow(len as u32 - 1)
                }
            })
            .sum::<i32>()
    );
}
