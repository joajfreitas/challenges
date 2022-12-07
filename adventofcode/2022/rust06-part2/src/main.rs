use std::collections::VecDeque;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn distinct_buffer(buffer: &VecDeque<char>) -> bool {
    for i in 0..buffer.len() {
        for j in i + 1..buffer.len() {
            if buffer[i] == buffer[j] {
                return false;
            }
        }
    }

    true
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let mut buffer: VecDeque<char> = VecDeque::with_capacity(4);
    let chars = input.trim().chars().collect::<Vec<char>>();

    for (index, char) in chars.iter().enumerate() {
        buffer.push_front(*char);
        buffer.truncate(14);

        if buffer.len() < 14 {
            continue;
        }
        if distinct_buffer(&buffer) {
            println!("{}", index + 1);
            break;
        }
    }
}
