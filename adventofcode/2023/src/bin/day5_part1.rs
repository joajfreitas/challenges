use rust_2023::read_aoc_input;
use std::env;

use regex::Regex;

#[derive(Debug)]
struct Map {
    dest: u32,
    source: u32,
    range: u32,
}

impl Map {
    fn new(dest: u32, source: u32, range: u32) -> Self {
        Map {
            dest,
            source,
            range,
        }
    }
}

fn compute_map(map: &Vec<Map>, input: u32) -> u32 {
    for mapping in map {
        if mapping.source <= input && input < mapping.source + mapping.range {
            return input - mapping.source + mapping.dest;
        }
    }

    input
}

fn compute(maps: &Vec<Vec<Map>>, seed: u32) -> u32 {
    let mut input = seed;
    for map in maps {
        input = compute_map(map, input);
    }

    input
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    let lines: Vec<&str> = input.lines().collect();

    let seeds: String = lines[0].chars().collect::<Vec<char>>()[7..]
        .into_iter()
        .collect();
    let list_re = Regex::new(r"(\d+) ?").unwrap();

    let seeds: Vec<u32> = list_re
        .captures_iter(&seeds)
        .map(|cap| cap.get(1).unwrap().as_str().parse::<u32>().unwrap())
        .collect();

    let mut maps: Vec<Vec<Map>> = Vec::new();

    let mut previous_empty_line = true;

    let mut acc: Vec<Map> = Vec::new();
    for line in &lines[2..] {
        if line == &String::from("") {
            previous_empty_line = true;
            maps.push(acc);
            acc = Vec::new();
            continue;
        }

        if previous_empty_line {
            previous_empty_line = false;
            continue;
        }

        let l: Vec<u32> = list_re
            .captures_iter(line)
            .map(|cap| cap.get(1).unwrap().as_str().parse::<u32>().unwrap())
            .collect();

        acc.push(Map::new(l[0], l[1], l[2]));
    }

    maps.push(acc);

    dbg!(dbg!(seeds
        .iter()
        .map(|seed| compute(&maps, *seed))
        .collect::<Vec<u32>>())
    .iter()
    .min());
}
