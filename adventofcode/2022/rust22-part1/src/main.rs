use regex;
use std::collections::HashMap;
use std::env;
use std::fs;

#[derive(Debug, Eq, PartialEq)]
enum Tile {
    Void,
    Empty,
    Wall,
}

impl Tile {
    fn new(c: char) -> Tile {
        match c {
            ' ' => Tile::Void,
            '.' => Tile::Empty,
            '#' => Tile::Wall,
            _ => panic!(),
        }
    }
}

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn wrap(map: &Vec<Vec<Tile>>, pos: (i32, i32), walk: (i32, i32)) -> (i32, i32) {
    match walk {
        (0,1) => {
            let index = map[pos.0 as usize].iter().enumerate().filter(|x| *x.1 != Tile::Void).map(|x| x.0).next().unwrap();
            if map[pos.0 as usize][index] == Tile::Wall {
                pos
            }
            else {
                (pos.0, index as i32)
            }
        },
        (0, -1) => {
            let index = map[pos.0 as usize].iter().enumerate().rev().filter(|x| *x.1 != Tile::Void).map(|x| x.0).next().unwrap();
            if map[pos.0 as usize][index] == Tile::Wall {
                pos
            }
            else {
                (pos.0, index as i32)
            }
        },
        (1,0) => {
            let mut index = 0;
            for i in 0..map.len() {
                if map[i][pos.1 as usize] != Tile::Void{
                    index = i;
                    break;
                }
            }

            if map[index][pos.1 as usize] == Tile::Wall {
                pos
            }
            else {
                (index as i32, pos.1)
            }
        },
        (-1, 0) => {
            let mut index = 0;
            for i in (0..map.len()).rev() {
                if map[i][pos.1 as usize] != Tile::Void{
                    index = i;
                    break;
                }
            }

            if map[index][pos.1 as usize] == Tile::Wall {
                pos
            }
            else {
                (index as i32, pos.1)
            }
        },
        _ => (0,0),
    }
}

fn next(map: &Vec<Vec<Tile>>, pos: (i32, i32), walk: (i32, i32)) -> (i32, i32) {
    if pos.0 + walk.0 >= map.len() as i32 || pos.1 + walk.1 >= map[0].len() as i32 || pos.1 + walk.1 < 0 || pos.0 + walk.0 < 0 {
        return wrap(map, pos, walk);
    }
    match map[(pos.0 + walk.0) as usize][(pos.1 + walk.1) as usize] {
        Tile::Void => wrap(map, pos, walk),
        Tile::Empty => (pos.0 + walk.0, pos.1 + walk.1),
        Tile::Wall => pos,
    }
}

fn walk(map: &Vec<Vec<Tile>>, state: (i32, i32, i8), distance: i32) -> (i32, i32, i8) {
    let walk_x = match state.2 {
        0 => 1,
        1 | 3 => 0,
        2 => -1,
        _ => panic!(),
    };

    let walk_y = match state.2 {
        1 => 1,
        0 | 2 => 0,
        3 => -1,
        _ => panic!(),
    };
    
    let mut pos: (i32, i32) = (state.0, state.1);
    for _ in 0..distance {
        pos = next(map, pos, (walk_y, walk_x));
    }

    (pos.0, pos.1, state.2)
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let instruction_re: regex::Regex = regex::Regex::new(r"(\d+|[A-Z])").unwrap();

    let mut map: Vec<Vec<Tile>> = Vec::new();

    let lines = input.lines().collect::<Vec<&str>>();
    for line in &lines {
        if *line == "" {
            break;
        }
        map.push(
            line.chars()
                .map(|char| Tile::new(char))
                .collect::<Vec<Tile>>(),
        );
    }

    let max_line_size = map.iter().map(|x| x.len()).max().unwrap();
    for line in &mut map {
        for _ in 0..(max_line_size - line.len()) {
            line.push(Tile::Void);
        }
    }
    
    let instructions = lines[lines.len() - 1];

    let mut state: (i32, i32, i8) = (0,0, 0);

    for (i, tile) in map[0].iter().enumerate() {
        if *tile == Tile::Empty  {
            state = (0,i as i32,0);
            break;
        }
    }
    for instruction in instruction_re.captures_iter(instructions) {
        let instruction = instruction.get(1).unwrap().as_str();
        if instruction.chars().collect::<Vec<char>>()[0].is_numeric() {
            state = walk(&map, state, instruction.parse::<i32>().unwrap());
        }
        else {
            if instruction == "R" {
                state.2 = (state.2 + 1).rem_euclid(4);
            }
            else if instruction == "L" {
                state.2 = (state.2 - 1).rem_euclid(4);
            }
        }
    }

    println!("{} {} {}", state.0 + 1, state.1 + 1, state.2);
    println!("{}", 1000*(state.0 + 1) + 4*(state.1 + 1) + state.2 as i32);
}
