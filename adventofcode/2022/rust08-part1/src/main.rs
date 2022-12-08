use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn walk(
    grid: &Vec<Vec<u32>>,
    location: (usize, usize),
    size: (usize, usize),
    direction: (i32, i32),
) -> bool {
    let source_height = grid[location.0][location.1];

    let mut row = location.0 as i32;
    let mut col = location.1 as i32;
    loop {
        row = row + direction.0;
        col = col + direction.1;

        // edge of the map
        if row == size.0 as i32 || col == size.1 as i32 || row == -1 || col == -1 {
            return true;
        }

        // blocked view
        if source_height <= grid[row as usize][col as usize] {
            return false;
        }
    }
}
fn is_visible(grid: &Vec<Vec<u32>>, location: (usize, usize), size: (usize, usize)) -> bool {
    if location.0 == 0 || location.1 == 0 || location.0 == size.0 - 1 || location.1 == size.1 - 1 {
        return true;
    }

    let w1 = walk(grid, location, size, (0, 1));
    let w2 = walk(grid, location, size, (1, 0));
    let w3 = walk(grid, location, size, (0, -1));
    let w4 = walk(grid, location, size, (-1, 0));
    w1 || w2 || w3 || w4
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

    let rows = grid.len();
    let cols = grid[0].len();

    let mut acc = 0;

    for i in 0..rows {
        for j in 0..cols {
            if is_visible(&grid, (i, j), (rows, cols)) {
                acc += 1;
            }
        }
    }
    println!("{}", acc);
}
