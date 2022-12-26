use regex;
use std::collections::HashMap;
use std::env;
use std::fs;

#[derive(Debug)]
enum Value {
    Constant(i64),
    Add((Box<Value>, Box<Value>)),
    Sub((Box<Value>, Box<Value>)),
    Mul((Box<Value>, Box<Value>)),
    Div((Box<Value>, Box<Value>)),
    Var(String),
}

impl Value {
    fn get_var(&self) -> String {
        match self {
            Value::Var(s) => s.clone(),
            _ => panic!(),
        }
    }
}

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn eval(operations: &HashMap<String, Value>, operation: String) -> i64 {
    match &operations[&operation] {
        Value::Constant(i) => *i,
        Value::Add((v1, v2)) => eval(operations, v1.get_var()) + eval(operations, v2.get_var()),
        Value::Sub((v1, v2)) => eval(operations, v1.get_var()) - eval(operations, v2.get_var()),
        Value::Mul((v1, v2)) => eval(operations, v1.get_var()) * eval(operations, v2.get_var()),
        Value::Div((v1, v2)) => eval(operations, v1.get_var()) / eval(operations, v2.get_var()),
        _ => panic!(),
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let mut operation: HashMap<String, Value> = HashMap::new();

    let constant_re: regex::Regex = regex::Regex::new(r"(\d+)").unwrap();
    let mul_re: regex::Regex = regex::Regex::new(r"([a-z]+) \* ([a-z]+)").unwrap();
    let add_re: regex::Regex = regex::Regex::new(r"([a-z]+) \+ ([a-z]+)").unwrap();
    let sub_re: regex::Regex = regex::Regex::new(r"([a-z]+) - ([a-z]+)").unwrap();
    let div_re: regex::Regex = regex::Regex::new(r"([a-z]+) / ([a-z]+)").unwrap();

    for line in input.lines() {
        let sp = line.split(":").collect::<Vec<&str>>();

        let value = if constant_re.is_match(sp[1]) {
            Value::Constant(sp[1].trim().parse::<i64>().unwrap())
        } else if mul_re.is_match(sp[1]) {
            let caps = mul_re.captures(sp[1]).unwrap();
            let op1 = caps.get(1).unwrap().as_str().trim();
            let op2 = caps.get(2).unwrap().as_str().trim();
            Value::Mul((
                Box::new(Value::Var(op1.to_string())),
                Box::new(Value::Var(op2.to_string())),
            ))
        } else if add_re.is_match(sp[1]) {
            let caps = add_re.captures(sp[1]).unwrap();
            let op1 = caps.get(1).unwrap().as_str().trim();
            let op2 = caps.get(2).unwrap().as_str().trim();
            Value::Add((
                Box::new(Value::Var(op1.to_string())),
                Box::new(Value::Var(op2.to_string())),
            ))
        } else if sub_re.is_match(sp[1]) {
            let caps = sub_re.captures(sp[1]).unwrap();
            let op1 = caps.get(1).unwrap().as_str().trim();
            let op2 = caps.get(2).unwrap().as_str().trim();
            Value::Sub((
                Box::new(Value::Var(op1.to_string())),
                Box::new(Value::Var(op2.to_string())),
            ))
        } else if div_re.is_match(sp[1]) {
            let caps = div_re.captures(sp[1]).unwrap();
            let op1 = caps.get(1).unwrap().as_str().trim();
            let op2 = caps.get(2).unwrap().as_str().trim();
            Value::Div((
                Box::new(Value::Var(op1.to_string())),
                Box::new(Value::Var(op2.to_string())),
            ))
        } else {
            Value::Constant(0)
        };
        operation.insert(sp[0].to_string(), value);
    }

    println!("{}", eval(&operation, "root".to_string()));
}
