use rust_2023::read_aoc_input;
use std::env;

use regex::Regex;

fn parse_line(line: &str) -> (i32, Vec<[i32; 3]>) {
    let parts = line.split(":").collect::<Vec<&str>>();

    let re = Regex::new(r"Game (\d+): ((((\d+) (blue|red|green),? ?)+;? ?)+)").unwrap();

    let caps = re.captures(line).unwrap();

    let mut sets: Vec<[i32; 3]> = Vec::new();

    let mut reds = 0;
    let mut blues = 0;
    let mut greens = 0;

    let game_number = caps.get(1).unwrap().as_str().parse::<i32>().unwrap();
    for round in caps
        .get(2)
        .unwrap()
        .as_str()
        .split("; ")
        .collect::<Vec<&str>>()
    {
        for cube in round.split(", ").collect::<Vec<&str>>() {
            let components = cube.split(" ").collect::<Vec<&str>>();
            let ammount = components[0].parse::<i32>().unwrap();
            let cube = components[1];

            match cube {
                "red" => reds = ammount,
                "blue" => blues = ammount,
                "green" => greens = ammount,
                _ => panic!(),
            };
        }
        sets.push([reds, greens, blues]);
    }

    (game_number, sets)
}

fn filter_sets(sets: Vec<[i32; 3]>) -> bool {
    for set in sets {
        if set[0] > 12 {
            return false;
        } else if set[1] > 13 {
            return false;
        } else if set[2] > 14 {
            return false;
        }
    }

    return true;
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!(
        "{}",
        input
            .lines()
            .map(parse_line)
            .filter(|line| filter_sets(line.clone().1))
            .map(|line| line.0)
            .sum::<i32>()
    );
}
