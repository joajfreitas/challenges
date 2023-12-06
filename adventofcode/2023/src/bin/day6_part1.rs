use rust_2023::read_aoc_input;
use std::env;

use regex::Regex;

fn compute_winnings(distance: u32, time: u32) -> u32 {
    let mut acc = 0;
    for i in 0..time {
        if i * (time - i) > distance {
            acc += 1;
        }
    }

    acc
}

fn main() {
    let times = vec![42, 89, 91, 89];
    let distance = vec![308, 1170, 1291, 1467];

    //let times = vec![7, 15, 30];
    //let distance = vec![  9 ,40, 200];

    dbg!((0..times.len())
        .map(|i| compute_winnings(distance[i], times[i]))
        .reduce(|x, y| x * y)
        .unwrap());
}
