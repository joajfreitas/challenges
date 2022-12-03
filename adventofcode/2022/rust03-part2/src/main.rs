use itertools::multizip;
use std::collections::HashSet;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn convert_priority(item: &char) -> u32 {
    if item.is_ascii_uppercase() {
        ((*item as u8) - ('A' as u8) + 27) as u32
    } else {
        ((*item as u8) - ('a' as u8) + 1) as u32
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!(
        "{:?}",
        multizip((
            input.lines().step_by(3),
            input.lines().skip(1).step_by(3),
            input.lines().skip(2).step_by(3)
        ))
        .map(|(line1, line2, line3)| {
            let first_set = line1.chars().collect::<HashSet<char>>();
            let second_set = line2.chars().collect::<HashSet<char>>();
            let third_set = line3.chars().collect::<HashSet<char>>();

            let inter1: HashSet<char> = first_set.intersection(&second_set).map(|x| *x).collect();
            let item = inter1.intersection(&third_set).into_iter().next().unwrap();

            convert_priority(item)
        })
        .sum::<u32>()
    );
}
