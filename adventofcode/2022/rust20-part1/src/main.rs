use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

#[derive(Debug)]
struct RingBuffer {
    buffer: Vec<i32>,
}

//fn sig(x: i32) -> i32 {
//    if x >= 0 {
//        1
//    } else {
//        -1
//    }
//}

impl RingBuffer {
    fn new(buffer: &Vec<i32>) -> RingBuffer {
        RingBuffer {
            buffer: buffer.clone(),
        }
    }

    fn get(&self, id: i32) -> i32 {
        self.buffer[id.rem_euclid(self.buffer.len() as i32) as usize]
    }

    fn set(&mut self, id: i32, value: i32) {
        let len = self.buffer.len();
        self.buffer[id.rem_euclid(len as i32) as usize] = value;
    }

    fn swap(&mut self, a: i32, b: i32) {
        let aux = self.get(a);
        self.set(a, self.get(b));
        self.set(b, aux);
    }

    fn rotate(&mut self, source: i32, amount: i32) {
        ///let acc = if source + amount <= 0 {
        ///    -1
        ///} else if source + amount >= self.buffer.len() as i32 {
        ///    1
        ///} else {
        ///    0
        ///};
        let dest = (source + amount).rem_euclid((self.buffer.len() - 1) as i32);

        if dest >= source {
            for i in 0..dest - source {
                self.swap(source + i, source + i + 1);
            }
        } else {
            for i in 0..source - dest {
                self.swap(source - i, source - i - 1);
            }
        };
    }

    fn find(&self, mark: i32) -> Option<i32> {
        for (i, value) in self.buffer.iter().enumerate() {
            if *value == mark {
                return Some(i as i32);
            }
        }
        None
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());
    let buffer = input
        .lines()
        .map(|line| line.parse::<i32>().unwrap())
        .collect::<Vec<i32>>();
    let mut ring = RingBuffer::new(&buffer);

    for value in buffer {
        let index = ring.find(value).unwrap();
        let value = ring.get(index);
        ring.rotate(index, value);
        println!("{:?}", ring);
    }

    let idx = ring.find(0).unwrap();

    println!(
        "{}",
        dbg!(ring.get(idx + 1000)) + dbg!(ring.get(idx + 2000)) + dbg!(ring.get(idx + 3000))
    );
}
