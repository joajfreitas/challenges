use rayon::prelude::*;
use std::collections::HashSet;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn check_intersection(first: &Vec<u32>, second: &Vec<u32>) -> bool {
    let first = (first[0]..first[1] + 1)
        .into_iter()
        .collect::<HashSet<u32>>();
    let second = (second[0]..second[1] + 1)
        .into_iter()
        .collect::<HashSet<u32>>();
    let intersection = first.intersection(&second).collect::<HashSet<&u32>>();
    intersection.len() > 0
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    let acc: u32 = input
        .lines()
        .collect::<Vec<&str>>()
        .par_iter()
        .map(|line| {
            let pairs = line.split(',').collect::<Vec<&str>>();
            let first_pair = pairs[0]
                .split('-')
                .map(|x| x.parse::<u32>().unwrap())
                .collect::<Vec<u32>>();
            let second_pair = pairs[1]
                .split('-')
                .map(|x| x.parse::<u32>().unwrap())
                .collect::<Vec<u32>>();

            if check_intersection(&first_pair, &second_pair) {
                1
            } else {
                0
            }
        })
        .sum();

    println!("{}", acc);
}
