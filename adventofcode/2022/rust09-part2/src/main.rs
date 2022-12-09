use lazy_static::lazy_static;
use regex;
use std::collections::HashSet;
use std::env;
use std::fs;

struct Rope {
    nodes: Vec<(i32, i32)>,
}

impl Rope {
    fn new() -> Rope {
        Rope {
            nodes: vec![
                (0, 0),
                (0, 0),
                (0, 0),
                (0, 0),
                (0, 0),
                (0, 0),
                (0, 0),
                (0, 0),
                (0, 0),
            ],
        }
    }

    fn get(self: &Self, index: usize) -> (i32, i32) {
        self.nodes[index]
    }

    fn set(self: &mut Self, index: usize, pos: (i32, i32)) {
        self.nodes[index] = pos;
    }
}

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn saturate(value: i32) -> i32 {
    if value >= 1 {
        1
    } else if value <= -1 {
        -1
    } else {
        0
    }
}

fn convert_direction(direction: &str) -> (i32, i32) {
    match direction {
        "U" => (1, 0),
        "D" => (-1, 0),
        "L" => (0, -1),
        "R" => (0, 1),
        _ => panic!(),
    }
}

fn read_line(line: &str) -> ((i32, i32), i32) {
    lazy_static! {
        static ref MOVE_RE: regex::Regex = regex::Regex::new(r"([R|U|L|D]) ([0-9]+)").unwrap();
    }
    let captures = MOVE_RE.captures(line).unwrap();
    let direction = convert_direction(captures.get(1).unwrap().as_str());
    let steps = captures.get(2).unwrap().as_str().parse::<i32>().unwrap();

    (direction, steps)
}

fn update_rope_nodes(rope: &mut Rope, next: (i32, i32), current: usize) {
    let pos = rope.get(current);
    let distance = (next.0 - pos.0, next.1 - pos.1);

    if distance.0 > 1 || distance.1 > 1 || distance.0 < -1 || distance.1 < -1 {
        rope.set(
            current,
            (pos.0 + saturate(distance.0), pos.1 + saturate(distance.1)),
        );
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    let lines = input.lines().collect::<Vec<&str>>();

    let mut visited_positions: HashSet<(i32, i32)> = HashSet::new();

    let mut head_current_position = (0, 0);
    let mut rope = Rope::new();

    visited_positions.insert(rope.get(8));

    for line in lines {
        let results = read_line(line);
        let direction = results.0;
        let steps = results.1;

        for _ in 0..steps {
            head_current_position.0 += direction.0;
            head_current_position.1 += direction.1;

            update_rope_nodes(&mut rope, head_current_position, 0);
            for i in 1..9 {
                let pos = rope.get(i - 1);
                update_rope_nodes(&mut rope, pos, i);
            }

            visited_positions.insert(rope.get(8));
        }
    }

    println!("{}", visited_positions.len());
}
