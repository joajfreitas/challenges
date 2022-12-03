use std::collections::HashSet;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!(
        "{:?}",
        input
            .lines()
            .map(|line| {
                let length = line.len();
                let first_set = line.chars().take(length / 2).collect::<HashSet<char>>();
                let second_set = line
                    .chars()
                    .skip(length / 2)
                    .take(length / 2)
                    .collect::<HashSet<char>>();

                let item = first_set
                    .intersection(&second_set)
                    .into_iter()
                    .next()
                    .unwrap();

                if item.is_ascii_uppercase() {
                    ((*item as u8) - ('A' as u8) + 27) as u32
                } else {
                    ((*item as u8) - ('a' as u8) + 1) as u32
                }
            })
            .sum::<u32>()
    );
}
