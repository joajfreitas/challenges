use rust_2023::read_aoc_input;
use std::env;

use std::collections::HashMap;

#[derive(Debug, Clone, Copy)]
enum Point {
    Symbol,
    Number(u32),
    Dot,
    Gear,
}

impl Point {
    fn is_symbol(&self) -> bool {
        match self {
            Point::Symbol => true,
            _ => false,
        }
    }

    fn is_gear(&self) -> bool {
        match self {
            Point::Gear => true,
            _ => false,
        }
    }
}

#[derive(Debug, Clone, Copy)]
enum State {
    Start,
    ParsingNumber,
    FoundGear,
}

fn parse_input(line: &str) -> Vec<Point> {
    line.chars()
        .map(|x| match x {
            '.' => Point::Dot,
            '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' => {
                Point::Number(x.to_digit(10).unwrap())
            }
            '*' => Point::Gear,
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

fn gear_around(map: &Vec<Vec<Point>>, y: usize, x: usize) -> Option<(i32, i32)> {
    for (x, y) in [
        (y as i32, x as i32 + 1),
        (y as i32, x as i32 - 1),
        (y as i32 + 1, x as i32),
        (y as i32 - 1, x as i32),
        (y as i32 + 1, x as i32 + 1),
        (y as i32 + 1, x as i32 - 1),
        (y as i32 - 1, x as i32 + 1),
        (y as i32 - 1, x as i32 - 1),
    ] {
        if map_get_point(map, x, y).is_gear() {
            return Some((x, y));
        }
    }

    None
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    let map = input.lines().map(parse_input).collect::<Vec<Vec<Point>>>();

    let mut part_numbers: Vec<u32> = Vec::new();

    let mut gears: HashMap<(i32, i32), Vec<u32>> = HashMap::default();

    let mut state = State::Start;

    let mut current_number = 0;
    let mut current_index = 0;
    let mut current_gear = (0, 0);
    for j in 0..map.len() {
        for i in (0..map[0].len()).rev() {
            let current_point = map[j][i];
            match state {
                State::Start => match current_point {
                    Point::Number(x) => {
                        let gear_index = gear_around(&map, j, i);
                        if gear_index.is_some() {
                            current_gear = gear_index.unwrap();
                            state = State::FoundGear;
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
                        let gear_index = gear_around(&map, j, i);
                        if gear_index.is_some() {
                            current_gear = gear_index.unwrap();
                            state = State::FoundGear;
                        }
                        current_number += x * 10_u32.pow(current_index);
                        current_index += 1;
                    }
                    _ => {
                        state = State::Start;
                    }
                },
                State::FoundGear => match current_point {
                    Point::Number(x) => {
                        current_number += x * 10_u32.pow(current_index);
                        current_index += 1;
                    }
                    _ => {
                        if gears.contains_key(&current_gear) {
                            gears.get_mut(&current_gear).unwrap().push(current_number);
                        } else {
                            gears.insert(current_gear, vec![current_number]);
                        }
                        state = State::Start;
                    }
                },
            };
        }
    }

    let mut acc = 0;
    for (_, value) in gears {
        if value.len() == 2 {
            acc += value[0] * value[1];
        }
    }

    println!("{}", acc);
}
