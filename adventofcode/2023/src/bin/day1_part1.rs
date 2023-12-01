use rust_2023::read_aoc_input;
use std::env;

fn find_first_digit(chars: &Vec<char>) -> Option<char> {
    let digits = vec!['1', '2', '3', '4', '5', '6', '7', '8', '9'];
    for char in chars {
        if digits.contains(&char) {
            return Some(*char);
        }
    }

    None
}

fn find_last_digit(chars: &Vec<char>) -> Option<char> {
    let digits = vec!['1', '2', '3', '4', '5', '6', '7', '8', '9'];
    for char in chars.iter().rev() {
        if digits.contains(char) {
            return Some(*char);
        }
    }

    None
}

fn find_digits(chars: &Vec<char>) -> u32 {

    10*(find_first_digit(chars).unwrap().to_digit(10).unwrap() - '0'.to_digit(10).unwrap()) + (find_last_digit(chars).unwrap().to_digit(10).unwrap() -'0'.to_digit(10).unwrap())
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!(
        "{:?}",
        input
            .lines()
            .map(|line| find_digits(&line.chars().collect::<Vec<char>>()
            )).collect::<Vec<u32>>().iter().sum::<u32>()
    );
}
