use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[derive(Debug)]
struct Line {
    x1: i32,
    y1: i32,
    x2: i32,
    y2: i32,
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    println!(
        "{:?}",
        input
            .split("\n")
            .filter(|x| *x != "")
            .map(|x| {
                let sp = x.split(" -> ").collect::<Vec<&str>>();
                sp.iter()
                    .zip(sp.iter().skip(1))
                    .map(|(v1, v2)| {
                        let v1 = v1.split(",").collect::<Vec<&str>>();
                        let x1 = v1[0].parse::<i32>().unwrap();
                        let y1 = v1[1].parse::<i32>().unwrap();
                        let v2 = v2.split(",").collect::<Vec<&str>>();
                        let x2 = v2[0].parse::<i32>().unwrap();
                        let y2 = v2[1].parse::<i32>().unwrap();
                        Line { x1, y1, x2, y2 }
                    })
                    .collect::<Vec<Line>>()
            })
            .flatten()
            .collect::<Vec<Line>>()
    );
}
