use rust_2023::read_aoc_input;
use std::env;

#[derive(Debug, Clone, Copy)]
enum Point {
    Symbol,
    Number(u32),
    Dot,
}

impl Point {
    fn is_symbol(&self) -> bool {
        match self {
            Point::Symbol => true,
            _ => false,
        }
    }
}

#[derive(Debug, Clone, Copy)]
enum State {
    Start,
    ParsingNumber,
    FoundPartNumber,
}

fn parse_input(line: &str) -> Vec<Point> {
    line.chars()
        .map(|x| match x {
            '.' => Point::Dot,
            '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' => {
                Point::Number(x.to_digit(10).unwrap())
            }
            _ => Point::Symbol,
        })
        .collect()
}

fn map_get_point(map: &Vec<Vec<Point>>, y: i32, x: i32) -> Point {
    if y >= map.len() as i32 || y < 0 || x < 0 || x >= map[0].len() as i32 {
        Point::Dot
    } else {
        map[y as usize][x as usize]
    }
}

fn symbol_around(map: &Vec<Vec<Point>>, y: usize, x: usize) -> bool {
    map_get_point(map, y as i32, x as i32 + 1).is_symbol()
        || map_get_point(map, y as i32, x as i32 - 1).is_symbol()
        || map_get_point(map, y as i32 + 1, x as i32).is_symbol()
        || map_get_point(map, y as i32 - 1, x as i32).is_symbol()
        || map_get_point(map, y as i32 + 1, x as i32 + 1).is_symbol()
        || map_get_point(map, y as i32 + 1, x as i32 - 1).is_symbol()
        || map_get_point(map, y as i32 - 1, x as i32 + 1).is_symbol()
        || map_get_point(map, y as i32 - 1, x as i32 - 1).is_symbol()
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    let map = input.lines().map(parse_input).collect::<Vec<Vec<Point>>>();

    let mut part_numbers: Vec<u32> = Vec::new();

    let mut state = State::Start;

    let mut current_number = 0;
    let mut current_index = 0;
    for j in 0..map.len() {
        for i in (0..map[0].len()).rev() {
            let current_point = map[j][i];
            match state {
                State::Start => match current_point {
                    Point::Number(x) => {
                        if symbol_around(&map, j, i) {
                            state = State::FoundPartNumber;
                        } else {
                            state = State::ParsingNumber;
                        }
                        current_number = x;
                        current_index = 1;
                    }
                    _ => {
                        continue;
                    }
                },
                State::ParsingNumber => match current_point {
                    Point::Number(x) => {
                        if symbol_around(&map, j, i) {
                            state = State::FoundPartNumber;
                        }
                        current_number += x * 10_u32.pow(current_index);
                        current_index += 1;
                    }
                    _ => {
                        state = State::Start;
                    }
                },
                State::FoundPartNumber => match current_point {
                    Point::Number(x) => {
                        current_number += x * 10_u32.pow(current_index);
                        current_index += 1;
                    }
                    _ => {
                        part_numbers.push(current_number);
                        state = State::Start;
                    }
                },
            };
        }
    }

    println!("{:?}", part_numbers.iter().sum::<u32>());
}
