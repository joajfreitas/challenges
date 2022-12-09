use itertools::multizip;
use rayon::prelude::*;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn convert_priority(item: &char) -> u32 {
    if item.is_ascii_uppercase() {
        ((*item as u8) - ('A' as u8) + 27) as u32
    } else {
        ((*item as u8) - ('a' as u8) + 1) as u32
    }
}

fn convert_char_to_index(c: char) -> usize {
    let c = c as u8;
    if c >= 'A' as u8 && c <= 'Z' as u8 {
        (c - ('A' as u8) + 27) as usize
    } else if c >= 'a' as u8 && c <= 'z' as u8 {
        (c - ('a' as u8)) as usize
    } else {
        panic!();
    }
}

fn convert_mask_to_char(mask: u64) -> char {
    let mut i = 0;
    loop {
        if (mask >> i) == 1 {
            break;
        }
        i += 1
    }
    if i < 27 {
        (i + ('a' as u8)) as char
    } else if i < 54 {
        (i - 27 + ('A' as u8)) as char
    } else {
        panic!();
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    println!(
        "{:?}",
        multizip((
            input.lines().step_by(3),
            input.lines().skip(1).step_by(3),
            input.lines().skip(2).step_by(3)
        ))
        //.collect::<Vec<(&str, &str, &str)>>()
        //.par_iter()
        .map(|(line1, line2, line3)| {
            let mut first_set: u64 = 0;
            let mut second_set: u64 = 0;
            let mut third_set: u64 = 0;

            for c in line1.chars() {
                first_set |= (1 as u64) << convert_char_to_index(c);
            }

            for c in line2.chars() {
                second_set |= (1 as u64) << convert_char_to_index(c);
            }

            for c in line3.chars() {
                third_set |= (1 as u64) << convert_char_to_index(c);
            }

            // set intersection
            let intersection: u64 = first_set & second_set & third_set;
            convert_priority(&convert_mask_to_char(intersection))
        })
        .sum::<u32>()
    );
}
