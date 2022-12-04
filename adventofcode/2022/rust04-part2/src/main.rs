use std::collections::HashSet;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn check_intersection(first: &Vec<u32>, second: &Vec<u32>) -> bool {
    (first[0] <= second[0] && first[1] >= second[1])
        || (first[0] <= second[0] && first[1] >= second[0])
        || (first[0] <= second[1] && first[1] >= second[1])
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    let acc: u32 = input
        .lines()
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

            if check_intersection(&first_pair, &second_pair)
                || check_intersection(&second_pair, &first_pair)
            {
                1
            } else {
                0
            }
        })
        .sum();

    println!("{}", acc);
}
