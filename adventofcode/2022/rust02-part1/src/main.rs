use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn convert(s: &str) -> Option<i8> {
    if s == "A" || s == "X" {
        return Some(0);
    } else if s == "B" || s == "Y" {
        return Some(1);
    } else if s == "C" || s == "Z" {
        return Some(2);
    }

    None
}

fn round(a: i8, b: i8) -> i8 {
    static play_matrix: [i8; 9] = [0, -1, 1, 1, 0, -1, -1, 1, 0];

    play_matrix[(3 * a + b) as usize]
}

fn score(play: i8, result: i8) -> i8 {
    play + 1 + 3 * (result + 1)
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

            let theirs = convert(sp[0].clone()).unwrap();
            let mine = convert(sp[1].clone()).unwrap();

            score(mine, round(mine, theirs)) as i32
        })
        .sum();

    println!("{}", result);
}
