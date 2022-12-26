use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn snafu_to_decimal(snafu: Vec<char>) -> i64 {
    snafu
        .iter()
        .rev()
        .enumerate()
        .map(|(i, x)| {
            dbg!((i, x));
            let base: i64 = match x {
                '=' => -2,
                '-' => -1,
                '0' => 0,
                '1' => 1,
                '2' => 2,
                _ => panic!(),
            };
            dbg!(base * 5i64.pow(i as u32))
        })
        .sum::<i64>()
}

fn decimal_to_snafu(number: i64) -> Vec<char> {
    let mut snafu: Vec<char> = Vec::new();
    let mut aux = number;

    loop {
        if aux == 0 {
            break;
        }
        let c = match (aux + 2) % 5 {
            0 => '=',
            1 => '-',
            2 => '0',
            3 => '1',
            4 => '2',
            _ => panic!(),
        };
        snafu.push(dbg!(c));
        aux = (aux + 2) / 5;
    }
    snafu
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    println!(
        "{:?}",
        decimal_to_snafu(
            input
                .lines()
                .map(|line| snafu_to_decimal(line.chars().collect::<Vec<char>>()))
                .sum::<i64>()
        )
        .iter()
        .rev()
        .cloned()
        .collect::<String>()
    );
}
