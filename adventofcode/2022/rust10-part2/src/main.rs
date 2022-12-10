use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn get_index(register: i32) -> (i32, i32) {
    (register / 40, register % 40)
}

fn register_results(screen: &mut Vec<Vec<bool>>, clock: i32, register: i32) {
    let clock = get_index(clock - 1);
    let index1 = get_index(register);
    let index2 = get_index(register - 1);
    let index3 = get_index(register + 1);

    if clock.1 == index1.1 || clock.1 == index2.1 || clock.1 == index3.1 {
        screen[clock.0 as usize][clock.1 as usize] = true;
    } else {
    }
}

fn print_screen(screen: Vec<Vec<bool>>) {
    for i in 0..6 {
        for j in 0..40 {
            if screen[i][j] {
                print!("#");
            } else {
                print!(".");
            }
        }
        print!("\n");
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let mut clock = 0;
    let mut register = 1;

    let mut screen: Vec<Vec<bool>> = Vec::new();
    for i in 0..6 {
        screen.push(Vec::new());
        for j in 0..40 {
            screen[i].push(false);
        }
    }

    for line in input.lines() {
        let sp = line.split(" ").collect::<Vec<&str>>();
        match sp[0] {
            "addx" => {
                for i in 0..2 {
                    if i == 0 {
                        clock += 1;
                        register_results(&mut screen, clock, register);
                    } else {
                        clock += 1;
                        register_results(&mut screen, clock, register);
                        register += sp[1].parse::<i32>().unwrap();
                    }
                }
            }
            "noop" => {
                clock += 1;
                register_results(&mut screen, clock, register);
            }
            _ => panic!(),
        };
    }

    print_screen(screen);
}
