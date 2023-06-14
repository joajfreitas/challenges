use regex;
use std::env;
use std::fs;
use std::cmp;

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

    fn reaches(&self, line: i32) -> bool {
        let top = self.sensor.1 + self.dist;
        let bottom = self.sensor.1 - self.dist;
        
        bottom <= line && top >= line
    }
}

fn compute_projected_line(diamond: &Diamond, y_proj: i32) -> (i32, i32) {
    let vdist = (y_proj - diamond.sensor.1).abs();
    let dist = diamond.dist - vdist;
    (diamond.sensor.0 - dist, diamond.sensor.0 + dist)
}

fn merge_line(line1: (i32, i32), line2: (i32, i32)) -> Option<(i32, i32)>{
    if line1.1 < line2.0  || line2.1 < line1.0 {
        return None;
    }
    
    let left = cmp::min(line1.0, line2.0);
    let right = cmp::max(line1.1, line2.1);
    Some((left,right))
}

fn main() {
    let line_number = 2000000;
    //let line_number = 10;

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
            Diamond::new(
                (sensor_x, sensor_y),
                (beacon_x, beacon_y),
            )
        })
        .collect::<Vec<Diamond>>();
    
    //find beacons is the interest line. Those are not counted as locations where a beacon cannot be
    let mut segments: Vec<(i32, i32)> = Vec::new();
    let mut insert = true;
    for line in lines {
        if !line.reaches(line_number) {
            continue;
        }
        
        let segment = compute_projected_line(&line, line_number);
        
        for i in 0..segments.len() {
            let merged = merge_line(segments[i], segment);
            if merged.is_some() {
                insert = false;
                segments[i] = merged.unwrap();
                break;
            }
            else {
                continue;
            }
        }
        if insert {
            segments.push(segment);
        }
        insert = true;
        
        for i in (0..segments.len()).rev() {
            if i <= 0 {
                break;
            }

            let r = merge_line(segments[i], segments[i-1]);
            if r.is_some() {
                segments[i-1] = r.unwrap();
                segments.remove(i);
            }
        }
    }
    
    println!("{:?}", segments.iter().map(|segment| (segment.1 - segment.0).abs()).sum::<i32>());
}

