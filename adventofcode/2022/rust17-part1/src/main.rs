use regex;
use std::env;
use std::fs;

#[derive(Debug, Clone)]
struct Rock {
    points: Vec<(i32, i32)>,
    position: (i32, i32),
}

impl Rock {
    fn new(points: Vec<(i32, i32)>, position: (i32, i32)) -> Rock {
        Rock { points, position }
    }
}

#[derive(Clone, Debug)]
enum Space {
    Free,
    Occupied,
}

#[derive(Clone, Debug, PartialEq, Eq)]
enum SimState {
    Settled,
    Running,
}

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

fn check_collision(rock: &Rock, limits: (i32, i32, i32, i32)) -> bool {
    for point in rock.points.iter() {
        let abs_location = (point.0 + rock.position.0, point.1 + rock.position.1);
        if abs_location.0 >= limits.0
            || abs_location.0 <= limits.2
            || abs_location.1 >= limits.1
            || abs_location.1 <= limits.3
        {
            return true;
        }
    }

    false
}

fn move_rock(rock: &mut Rock, direction: (i32, i32)) {
    rock.position.0 = rock.position.0 + direction.0;
    rock.position.1 = rock.position.1 + direction.1;
}

fn etch_rock(map: &mut Vec<Vec<Space>>, rock: &Rock) {
    for point in rock.points.iter() {
        map[(rock.position.0 + point.0) as usize][(rock.position.1 + point.1) as usize] =
            Space::Occupied;
    }
}

fn get_highest_point(rock: &Rock) -> (i32, i32) {
    rock.points
        .iter()
        .map(|point| (rock.position.0 + point.0, rock.position.1 + point.1))
        .max()
        .unwrap()
}

fn display(map: &Vec<Vec<Space>>) {
    for row in map.iter().rev() {
        for col in row.iter() {
            print!(
                "{}",
                match col {
                    Space::Free => '.',
                    Space::Occupied => '#',
                }
            );
        }
        print!("\n");
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let mut curr_shape = 0;
    let shapes: Vec<Vec<(i32, i32)>> = vec![
        vec![(0, 0), (0, 1), (0, 2), (0, 3)],
        vec![(0, 1), (1, 0), (1, 1), (2, 1), (1, 2)],
        vec![(0, 0), (0, 1), (0, 2), (1, 2), (2, 2)],
        vec![(0, 0), (1, 0), (2, 0), (3, 0)],
        vec![(0, 0), (0, 1), (1, 0), (1, 1)],
    ];

    let mut map: Vec<Vec<Space>> = vec![vec![Space::Free; 7]; 8092];

    let mut highest_point = (0, 0);

    let mut sim_state: SimState = SimState::Settled;

    let mut falling_rock = Rock::new(shapes[curr_shape].clone(), (0, 0));
    let mut falling_rock_pos = (0, 0);

    loop {
        println!("{:?}", falling_rock);
        if sim_state == SimState::Settled {
            falling_rock = Rock::new(shapes[curr_shape].clone(), (highest_point.0 + 3, 2));
            falling_rock_pos = (highest_point.0 + 2, 2);
            sim_state = SimState::Running;
        } else {
            if check_collision(&falling_rock, (8092, 7, highest_point.0, 0)) {
                etch_rock(&mut map, &falling_rock);
                display(&map);
                highest_point = get_highest_point(&falling_rock);
                sim_state = SimState::Settled;
                println!("finished falling");
            } else {
                println!("move rock");
                move_rock(&mut falling_rock, (-1, 0));
            }
        }
    }
}
