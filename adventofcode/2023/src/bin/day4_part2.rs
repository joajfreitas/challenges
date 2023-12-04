use rust_2023::read_aoc_input;
use std::env;

use std::collections::{HashMap, HashSet};

use regex::Regex;

fn parse_input(line: &str) -> (u32, HashSet<u32>, HashSet<u32>) {
    let line_re = Regex::new(r"Card +(\d+):(.+)\|(.+)").unwrap();
    let number_re = Regex::new(r" +(\d+)").unwrap();

    let caps = line_re.captures(line).unwrap();

    let card_number = caps.get(1).unwrap().as_str().parse::<u32>().unwrap();
    let winning_numbers = caps.get(2).unwrap().as_str();
    let your_numbers = caps.get(3).unwrap().as_str();

    let winning_numbers: HashSet<u32> = number_re
        .captures_iter(winning_numbers)
        .map(|cap| cap.get(1).unwrap().as_str().parse::<u32>().unwrap())
        .collect();
    let your_numbers: HashSet<u32> = number_re
        .captures_iter(your_numbers)
        .map(|cap| cap.get(1).unwrap().as_str().parse::<u32>().unwrap())
        .collect();

    (card_number, winning_numbers, your_numbers)
}

fn winning_cards(current_card: u32, card: &Vec<u32>) -> Vec<u32> {
    card.iter()
        .filter(|x| **x > current_card)
        .map(|x| *x)
        .collect()
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = read_aoc_input(args.get(1).unwrap());

    let cards: Vec<usize> = input
        .lines()
        .map(parse_input)
        .map(|line| {
            line.1
                .intersection(&line.2)
                .map(|x| *x)
                .collect::<Vec<u32>>()
                .len()
        })
        .collect();

    let mut collect_cards: HashMap<u32, u32> = HashMap::default();

    for (i, _) in cards.iter().enumerate() {
        collect_cards.insert(i as u32, 1);
    }

    for (i, card) in cards.iter().enumerate() {
        let ammount = dbg!(collect_cards.get(&(i as u32)).unwrap()).clone();
        println!("{:?}", collect_cards);
        let x = i as u32 + 1;
        for index in x..(x + (*card as u32)) {
            let v = dbg!(collect_cards.get(&(index as u32)).unwrap()).clone();
            collect_cards.insert(dbg!(index as u32), dbg!(ammount + v));
        }
    }

    println!("{}", collect_cards.values().sum::<u32>());
}
