use regex;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[derive(Debug, Clone)]
enum Operation {
    Sum,
    Mul,
}

#[derive(Debug, Clone)]
enum Operand {
    Var,
    Const(i64),
}

#[derive(Debug, Clone)]
struct Monkey {
    items: Vec<i64>,
    operation: Operation,
    operand: Operand,
    test: i64,
    t: i64,
    f: i64,
    inspections: i64,
}

impl Monkey {
    fn new(
        items: Vec<i64>,
        operation: Operation,
        operand: Operand,
        test: i64,
        t: i64,
        f: i64,
    ) -> Monkey {
        Monkey {
            items: items,
            operation: operation,
            operand: operand,
            test: test,
            t: t,
            f: f,
            inspections: 0,
        }
    }
}

fn get_operand(monkey: &Monkey, item: &i64) -> i64 {
    match &monkey.operand {
        Operand::Const(v) => v.clone(),
        Operand::Var => item.clone(),
    }
}

fn operation(monkey: &Monkey, item: &i64, operand: i64) -> i64 {
    match monkey.operation {
        Operation::Sum => item + operand,
        Operation::Mul => item * operand,
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let re = regex::Regex::new(r"Monkey (?P<monkey>\d):\s+Starting items:(?P<items>(\s\d{1,3},)*)\s(?P<last>\d{1,3})\s+Operation: new = old (?P<op>[\*\+]) (?P<operand>\d{1,3}|old)\s+Test: divisible by (?P<test>\d{1,3})\s+If true: throw to monkey (?P<true>\d)\s+If false: throw to monkey (?P<false>\d)").unwrap();

    let mut monkeys = re
        .captures_iter(&input)
        .map(|cap| {
            let mut items = cap
                .name("items")
                .unwrap()
                .as_str()
                .split(",")
                .filter(|x| *x != "")
                .map(|x| x.trim().parse::<i64>().unwrap())
                .collect::<Vec<i64>>();

            items.push(cap.name("last").unwrap().as_str().parse::<i64>().unwrap());

            let operation = match cap.name("op").unwrap().as_str() {
                "+" => Operation::Sum,
                "*" => Operation::Mul,
                _ => panic!(),
            };

            let operand = match cap.name("operand").unwrap().as_str() {
                "old" => Operand::Var,
                other => Operand::Const(other.parse::<i64>().unwrap()),
            };
            let test = cap.name("test").unwrap().as_str().parse::<i64>().unwrap();
            let t = cap.name("true").unwrap().as_str().parse::<i64>().unwrap();
            let f = cap.name("false").unwrap().as_str().parse::<i64>().unwrap();

            items.reverse();
            Monkey::new(items, operation, operand, test, t, f)
        })
        .collect::<Vec<Monkey>>();

    let divs = monkeys.iter().map(|monkey| monkey.test).product::<i64>();

    for _ in 0..10000 {
        for id in 0..monkeys.len() {
            let monkey = monkeys[id].clone();
            for item in monkey.items.iter().rev() {
                monkeys[id].inspections += 1;

                let operand = get_operand(&monkey, item);
                let new = operation(&monkey, item, operand);

                if new.clone() % monkey.test == 0 {
                    let target: &mut Monkey = &mut monkeys[monkey.t as usize];
                    target.items.insert(0, new % divs);
                    monkeys[id].items.pop();
                } else {
                    let target: &mut Monkey = &mut monkeys[monkey.f as usize];
                    target.items.insert(0, new % divs);
                    monkeys[id].items.pop();
                }
            }
        }
    }
    println!(
        "{:?}",
        monkeys.iter().map(|x| x.inspections).collect::<Vec<i64>>()
    );
}
