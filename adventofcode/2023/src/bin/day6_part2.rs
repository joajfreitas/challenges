use rust_2023::read_aoc_input;
use std::env;

use regex::Regex;

fn compute_winnings(distance: u64, time: u64) -> u64 {
    let mut start = 0;
    let mut end = 0;
    for i in 0..time {
        if i * (time - i) > distance {
            start = i;
        }
    }

    for i in (0..time).rev() {
        if i * (time - i) > distance {
            end = i;
        }
    }
    dbg!(start) - dbg!(end) + 1
}

fn main() {
    let time: u64 = 42899189;
    let distance: u64 = 308117012911467;

    //let time = 71530;
    //let distance = 940200;

    dbg!(compute_winnings(distance, time));
}
