use regex;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

struct Diamond {
    sensor: (i32, i32),
    dist: i32,
}

impl Diamond {
    fn new(sensor: (i32, i32), beacon: (i32, i32)) -> Diamond {
        Diamond {
            sensor,
            dist: (sensor.0 - beacon.0).abs() + (sensor.1 - beacon.1).abs()
        }
    }
    
    fn contains_unseen_points(&self, quadrant: ((i32, i32), (i32, i32))) -> bool {
        let corners = vec![
            (quadrant.0.0, quadrant.0.1),
            (quadrant.1.0, quadrant.0.1),
            (quadrant.0.0, quadrant.1.1),
            (quadrant.1.0, quadrant.1.1),
        ];

        let max_dist = corners.iter().map(|corner| (corner.0 - self.sensor.0).abs() + (corner.1 - self.sensor.1).abs()).max().unwrap();

        max_dist > self.dist
    }

    fn within_sensor_range(&self, other: (i32, i32)) -> bool {
        let distance = (self.sensor.0 - other.0).abs() + (self.sensor.1 - other.1).abs();
        distance <= self.dist
    }
}

fn compute_quadrants(square:((i32, i32), (i32, i32))) -> Vec<((i32, i32), (i32,i32))> {

    let middle = ((square.1.0+square.0.0)/2,(square.0.1 + square.1.1)/2);
    vec![
        (square.0, middle),
        ((middle.0+1,square.0.1), (square.1.0, middle.1)),
        ((square.0.0, middle.1+1), (middle.0, square.1.1)),
        ((middle.0, middle.1 + 1), square.1),
    ]
}



fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    let re = regex::Regex::new(
        r"Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)",
    )
    .unwrap();
    let diamonds = re
        .captures_iter(&input)
        .map(|capture| {
            let sensor_x = capture.get(1).unwrap().as_str().parse::<i32>().unwrap();
            let sensor_y = capture.get(2).unwrap().as_str().parse::<i32>().unwrap();
            let beacon_x = capture.get(3).unwrap().as_str().parse::<i32>().unwrap();
            let beacon_y = capture.get(4).unwrap().as_str().parse::<i32>().unwrap();
            Diamond::new(
                (sensor_x, sensor_y),
                (beacon_x, beacon_y),
            )
        })
        .collect::<Vec<Diamond>>();
    
    let mut quadrant_stack = compute_quadrants(((0,0),(4000000,4000000)));
    
    while let Some(quadrant) = quadrant_stack.pop() {
        if quadrant.0 == quadrant.1{
            if diamonds.iter().all(|diamond| !diamond.within_sensor_range(quadrant.0)) {
                println!("{}",4000000 * (quadrant.0.0 as i64) + (quadrant.0.1 as i64));
                break;
            }
        }
        for quadrant in compute_quadrants(quadrant) {
            if quadrant.0.0 > quadrant.1.0 || quadrant.0.1 > quadrant.1.1 {
                continue;
            }
            if diamonds.iter().all(|diamond| diamond.contains_unseen_points(quadrant)) {
                quadrant_stack.push(quadrant);
            }
        }
    }
}

