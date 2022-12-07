use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn convert(s: &str) -> i8 {
    if s == "A" {
        return 0;
    } else if s == "B" {
        return 1;
    } else if s == "C" {
        return 2;
    }

    panic!();
}

fn convert_result(s: &str) -> i8 {
    if s == "X" {
        return -1;
    } else if s == "Y" {
        return 0;
    } else if s == "Z" {
        return 1;
    }

    panic!();
}

fn round(result: i8, theirs: i8) -> (i8, i8) {
    static PLAY_MATRIX: [i8; 9] = [0, -1, 1, 1, 0, -1, -1, 1, 0];

    let mut index = 0;
    for (i, r) in PLAY_MATRIX
        .iter()
        .skip(3 * theirs as usize)
        .take(3)
        .enumerate()
    {
        if -*r == result {
            index = i;
        }
    }

    (index as i8, result)
}

fn score(play: (i8, i8)) -> i8 {
    play.0 + 1 + 3 * (play.1 + 1)
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    let result: i32 = input
        .lines()
        .collect::<Vec<&str>>()
        .iter()
        .map(|line| {
            let sp = line.split(" ").collect::<Vec<&str>>();

            let theirs = convert(sp[0].clone());
            let result = convert_result(sp[1].clone());

            score(round(result, theirs)) as i32
        })
        .sum();

    println!("{}", result);
}
