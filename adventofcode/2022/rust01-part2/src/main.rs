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
    let mut m2 = 0;
    let mut m3 = 0;

    for line in input.lines() {
        if line == "" {
            if acc > m1 {
                m3 = m2;
                m2 = m1;
                m1 = acc;
            }
            else if acc > m2 {
                m3 = m2;
                m2 = acc;
            }
            else if acc > m3 {
                m3 = acc;
            }

            acc = 0;
            continue;
        }

        acc += line.parse::<i32>().unwrap();
    }

    println!("sum: {}", m1 + m2 + m3);
}
