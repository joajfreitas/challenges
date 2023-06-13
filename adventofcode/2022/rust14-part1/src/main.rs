use std::env;
use std::fs;
use std::cmp;
use std::fmt;
use std::collections::HashMap;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[derive(Debug)]
struct Line {
    x1: i32,
    y1: i32,
    x2: i32,
    y2: i32,
}


#[derive(Debug, Clone, PartialEq, Eq)]
enum Space {
    Empty,
    Wall,
    Sand,
}

impl fmt::Display for Space {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Space::Empty => write!(f, "."),
            Space::Wall => write!(f, "#"),
            Space::Sand => write!(f, "o"),
        }
    }
}


#[derive(Clone, Debug, Eq, PartialEq)]
enum SimState {
    Settled,
    Running,
    Done,
}


struct Sim {
    last: (i32, i32),
    bounds: ((i32, i32), (i32, i32)),
    map: HashMap::<(i32, i32), Space>,
    state: SimState,
}

impl Sim {
    fn new(map: HashMap<(i32, i32), Space>, bounds: ((i32, i32), (i32, i32))) -> Sim {
        Sim {
            map,
            bounds,
            last: (0,0),
            state: SimState::Settled,
        }
    }

    fn occupied(&self, pos:&(i32, i32)) -> bool {
        self.map[pos] == Space::Wall || self.map[pos] == Space::Sand
    }
    
    fn out_of_bounds(&self, pos: (i32, i32)) -> bool {
        pos.0 <= self.bounds.0.0 || pos.0 >= self.bounds.0.1 || pos.1 <= self.bounds.1.0 || pos.1 >= self.bounds.1.1
    }

    fn next(&self) -> Option<(i32, i32)> {
        let bottom = (self.last.0+1, self.last.1);
        let bottom_left = (self.last.0+1, self.last.1-1);
        let bottom_right = (self.last.0+1, self.last.1+
            1);
        if !self.occupied(&bottom) {
            Some(bottom)
        }
        else if !self.occupied(&bottom_left) {
            Some(bottom_left)
        }
        else if !self.occupied(&bottom_right) {
            Some(bottom_right)
        }
        else {
            None
        }
    }


    fn sim(&mut self){
        if self.state == SimState::Settled {
            self.map.insert((0, 500), Space::Sand);
            self.last = (0,500);
            self.state = SimState::Running;
            return;
        }
        else {
            let next_pos = self.next();
            if next_pos.is_none() {
                self.state = SimState::Settled;
                return
            }
            else {
                let next_pos = next_pos.unwrap();
                self.map.insert(next_pos, Space::Sand);
                self.map.insert(self.last, Space::Empty);
                self.last = next_pos;
                if self.out_of_bounds(next_pos) {
                    self.state = SimState::Done;
                }
            }
        }

    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    let lines = input
            .split("\n")
            .filter(|x| *x != "")
            .map(|x| {
                let sp = x.split(" -> ").collect::<Vec<&str>>();
                sp.iter()
                    .zip(sp.iter().skip(1))
                    .map(|(v1, v2)| {
                        let v1 = v1.split(",").collect::<Vec<&str>>();
                        let x1 = v1[0].parse::<i32>().unwrap();
                        let y1 = v1[1].parse::<i32>().unwrap();
                        let v2 = v2.split(",").collect::<Vec<&str>>();
                        let x2 = v2[0].parse::<i32>().unwrap();
                        let y2 = v2[1].parse::<i32>().unwrap();
                        Line { x1, y1, x2, y2 }
                    })
                    .collect::<Vec<Line>>()
            })
            .flatten()
            .collect::<Vec<Line>>();

    let leftmost = lines.iter().map(|line| cmp::min(line.x1, line.x2)).min().unwrap();
    let rightmost = lines.iter().map(|line| cmp::max(line.x1, line.x2)).max().unwrap();
    let topmost = 0;
    let bottommost = lines.iter().map(|line| cmp::max(line.y1, line.y2)).max().unwrap();
    
    println!("{} {} {} {}", leftmost, rightmost, topmost, bottommost);

    let mut map: HashMap<(i32, i32), Space> = HashMap::new();
    
    
    for col in leftmost..rightmost+1 {
        for row in topmost..bottommost + 1 {
            map.insert((row, col), Space::Empty);
        }
    }

    for line in lines {
        for i in (cmp::min(line.x1,line.x2))..(cmp::max(line.x1, line.x2)+1) {
            for j in (cmp::min(line.y1,line.y2))..(cmp::max(line.y1, line.y2)+1) {
                map.insert((j,i), Space::Wall);
            }
        }
    }
    
    let mut sim = Sim::new(map, ((topmost, bottommost), (leftmost, rightmost)));
    //println!("{:?}", map.keys());
    //
    //
    let mut acc = 0;
    loop {
        sim.sim();
        if sim.state == SimState::Settled{
            acc += 1;
        }
        if sim.state == SimState::Done {
            break;
        }

    }

    println!("{}", acc);
}
