use rust_2023::read_aoc_input;
use std::env;

use regex::Regex;

fn find_digit(word: &str) -> u64 {
    let word_re = Regex::new(r"[0-9]|(zero|one|two|three|four|five|six|seven|eight|nine)").unwrap();

    let captures = word_re
        .find_iter(word)
        .map(|m| match m.as_str() {
            "0" | "zero" => 0,
            "1" | "one" => 1,
            "2" | "two" => 2,
            "3" | "three" => 3,
            "4" | "four" => 4,
            "5" | "five" => 5,
            "6" | "six" => 6,
            "7" | "seven" => 7,
            "8" | "eight" => 8,
            "9" | "nine" => 9,
            _ => panic!(),
        })
        .collect::<Vec<u32>>();

    (10 * captures.iter().next().unwrap() + captures.iter().rev().next().unwrap()).into()
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!(
        "{:?}",
        dbg!(input
            .lines()
            .map(|line| find_digit(&line))
            .collect::<Vec<u64>>())
        .iter()
        .sum::<u64>()
    );
}
