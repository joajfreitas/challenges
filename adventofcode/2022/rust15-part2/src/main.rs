use regex;
use std::collections::HashSet;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[derive(Debug, Copy, Clone, Eq, PartialEq)]
enum State {
    Empty,
    Occupied,
}

fn display(map: &Vec<Vec<State>>, origin: (i32, i32)) {
    print!("   ");
    for (j,_) in map[0].iter().enumerate() {
        print!("{}", (j as i32+origin.1 ).abs()/10);
    }
    print!("\n");
    print!("   ");
    for (j,_) in map[0].iter().enumerate() {
        print!("{}", (j as i32+origin.1 ).abs()%10);
    }
    print!("\n");
    for (i,row) in map.iter().enumerate() {
        print!("{:2} ", i as i32 + origin.0);
        for col in row {
            print!(
                "{}",
                match col {
                    State::Empty => ".",
                    State::Occupied => "#",
                }
            );
        }
        print!("\n");
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    let re = regex::Regex::new(
        r"Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)",
    )
    .unwrap();
    let lines = re
        .captures_iter(&input)
        .map(|capture| {
            let sensor_x = capture.get(1).unwrap().as_str().parse::<i32>().unwrap();
            let sensor_y = capture.get(2).unwrap().as_str().parse::<i32>().unwrap();
            let beacon_x = capture.get(3).unwrap().as_str().parse::<i32>().unwrap();
            let beacon_y = capture.get(4).unwrap().as_str().parse::<i32>().unwrap();
            (
                sensor_x,
                sensor_y,
                beacon_x,
                beacon_y,
                (sensor_x - beacon_x).abs() + (sensor_y - beacon_y).abs(),
            )
        })
        .collect::<Vec<(i32, i32, i32, i32, i32)>>();
    
    // GARBAGE
    //let left_limit = lines.iter().map(|x| x.0 - x.4).min().unwrap();
    //let right_limit = lines.iter().map(|x| x.0 + x.4).max().unwrap();
    //let top_limit = lines.iter().map(|x| x.1 - x.4).min().unwrap();
    //let bottom_limit = lines.iter().map(|x| x.1 + x.4).max().unwrap();

    //let size = (right_limit - left_limit, bottom_limit - top_limit);
    //let origin = (left_limit, top_limit);

    //let mut map: Vec<Vec<State>> = Vec::new();

    //for _ in 0..(size.0 + 1) {
    //    map.push(
    //        (0..(size.1 + 1))
    //            .map(|x| State::Empty)
    //            .collect::<Vec<State>>(),
    //    );
    //}

    //for line in lines {
    //    for i in -line.4..line.4+1 {
    //        for j in -line.4..line.4+1 {
    //            if (dbg!(i).abs() + dbg!(j).abs()) <= line.4 {
    //                dbg!(line.4);
    //                dbg!((i+j).abs());
    //                map[(i + line.0 - origin.0) as usize]
    //                    [(j + line.1 - origin.1) as usize] = State::Occupied;
    //            }
    //        }
    //    }
    //}

    //display(&map, origin);
    //println!(
    //    "{:?}",
    //    map.iter()
    //        .enumerate()
    //        .map(|(i, x)| x
    //            .iter()
    //            .enumerate()
    //            .filter(|(j, y)| *j as i32 == 10 - origin.1)
    //            .map(move |(j, y)| (i.clone(), j, y)))
    //        .flatten()
    //        .filter(|(x, y, state)| **state == State::Occupied)
    //        .collect::<Vec<(usize, usize, &State)>>()
    //        .len() -1
    //);
}
