use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn register_results(results: i32, clock: i32, register: i32) -> i32 {
    if (clock - 20) % 40 == 0 {
        return results + clock * register;
    }
    results
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let mut clock = 0;
    let mut register = 1;

    let mut results: i32 = 0;

    for line in input.lines() {
        let sp = line.split(" ").collect::<Vec<&str>>();
        match sp[0] {
            "addx" => {
                for i in 0..2 {
                    if i == 0 {
                        clock += 1;
                        results = register_results(results, clock, register);
                    } else {
                        clock += 1;
                        results = register_results(results, clock, register);
                        register += sp[1].parse::<i32>().unwrap();
                    }
                }
            }
            "noop" => {
                clock += 1;
                results = register_results(results, clock, register);
            }
            _ => panic!(),
        };
    }

    println!("{}", results);
}
