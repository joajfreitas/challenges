use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap()
}

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let input = read_aoc_input(args.get(1).unwrap());
    
    let mut acc = 0;

    let mut m1 = 0;

    for line in input.lines() {
        if line == "" {
            if acc > m1 {
                m1 = acc;
            }

            acc = 0;
            continue;
        }

        acc += line.parse::<i32>().unwrap();
    }

    println!("max: {}", m1);
}
