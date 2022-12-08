use itertools::Itertools;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn walk(
    grid: &Vec<Vec<u32>>,
    location: (i32, i32),
    size: (i32, i32),
    direction: (i32, i32),
) -> i32 {
    let source_height = grid[location.0 as usize][location.1 as usize];

    let mut score = 0;
    let mut row = location.0;
    let mut col = location.1;
    loop {
        row = row + direction.0;
        col = col + direction.1;

        // edge of the map
        if row == size.0 as i32 || col == size.1 as i32 || row == -1 || col == -1 {
            return score;
        }

        // blocked view
        if source_height <= grid[row as usize][col as usize] {
            return score + 1;
        }

        score += 1;
    }
}
fn is_visible(grid: &Vec<Vec<u32>>, location: (i32, i32), size: (i32, i32)) -> i32 {
    let w1 = walk(grid, location, size, (0, 1));
    let w2 = walk(grid, location, size, (1, 0));
    let w3 = walk(grid, location, size, (0, -1));
    let w4 = walk(grid, location, size, (-1, 0));
    w1 * w2 * w3 * w4
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let grid = input
        .lines()
        .map(|line| {
            line.chars()
                .map(|x| x.to_digit(10).unwrap())
                .collect::<Vec<u32>>()
        })
        .collect::<Vec<Vec<u32>>>();

    let rows = grid.len() as i32;
    let cols = grid[0].len() as i32;

    println!(
        "{:?}",
        (0..rows)
            .cartesian_product(0..cols)
            .map(|(row, col)| is_visible(&grid, (row, col), (rows, cols)))
            .max()
            .unwrap()
    );
}
