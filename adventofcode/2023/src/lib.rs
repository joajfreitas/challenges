use std::fs;

pub fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}
