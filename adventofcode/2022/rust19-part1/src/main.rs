use regex;
use std::env;
use std::fs;

fn read_aoc_input(filename: &String) -> String {
    return fs::read_to_string(filename).unwrap();
}

struct Cost {
    ore: (i32, i32, i32),
    clay: (i32, i32, i32),
    obsidian: (i32, i32, i32),
    geode: (i32, i32, i32),
}

#[derive(Debug)]
struct State {
    ore: i32,
    clay: i32,
    obsidian: i32,
    geode: i32,
    ore_robots: i32,
    clay_robots: i32,
    obsidian_robots: i32,
    geode_robots: i32,
    time: i32,
}

impl State {
    fn new(
        ore: i32,
        clay: i32,
        obsidian: i32,
        geode: i32,
        ore_robots: i32,
        clay_robots: i32,
        obsidian_robots: i32,
        geode_robots: i32,
        time: i32,
    ) -> State {
        State {
            ore,
            clay,
            obsidian,
            geode,
            ore_robots,
            clay_robots,
            obsidian_robots,
            geode_robots,
            time,
        }
    }
}

fn next(state: &State, cost: &Cost) -> Vec<State> {
    let mut ore = state.ore + state.ore_robots;
    let clay = state.clay + state.clay_robots;
    let obsidian = state.obsidian + state.obsidian_robots;
    let geode = state.geode + state.geode_robots;
    let time = state.time + 1;

    let mut next_states: Vec<State> = Vec::new();
    let inc_robot_ore = if cost.ore.0 < state.ore {
        ore -= cost.ore.0;
        1
    } else {
        0
    };

    next_states.push(State::new(
        ore,
        clay,
        obsidian,
        geode,
        state.ore_robots,
        state.clay_robots,
        state.obsidian_robots,
        state.geode_robots,
        time,
    ));

    for ore_robots in 0..state.ore / cost.ore.0 {
        next_states.push(State::new(
            ore - ore_robots * cost.ore.0,
            clay,
            obsidian,
            geode,
            state.ore_robots + ore_robots,
            state.clay_robots,
            state.obsidian_robots,
            state.geode_robots,
            time,
        ));
        for clay_robots in 0..state.clay / cost.clay.0 {
            next_states.push(State::new(
                ore - ore_robots * cost.ore.0 - clay_robots * cost.clay.0,
                clay,
                obsidian,
                geode,
                state.ore_robots + ore_robots,
                state.clay_robots + clay_robots,
                state.obsidian_robots,
                state.geode_robots,
                time,
            ));
        }
    }

    next_states
}

fn goal(state: &State) -> bool {
    state.time == 20
}

fn solve(initial: &State, cost: &Cost) {
    for state in next(initial, cost) {
        if goal(&state) {
            return;
        }
        println!("{:?}", state);
        solve(&state, cost);
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = read_aoc_input(args.get(1).unwrap());

    let re: regex::Regex = regex::Regex::new(r"Blueprint (\d+): Each ore robot costs (\d+) ore\. Each clay robot costs (\d+) ore\. Each obsidian robot costs (\d+) ore and (\d+) clay\. Each geode robot costs (\d+) ore and (\d+) obsidian\.").unwrap();
    for cap in re.captures_iter(&input) {
        //println!("{:?}\n", cap);
        let id = cap.get(1).unwrap().as_str().parse::<i32>().unwrap();
        println!("================{}================", id);
        let ore_cost = cap.get(2).unwrap().as_str().parse::<i32>().unwrap();
        let clay_cost = cap.get(3).unwrap().as_str().parse::<i32>().unwrap();
        let obsidian_robot_ore_cost = cap.get(4).unwrap().as_str().parse::<i32>().unwrap();
        let obsidian_robot_clay_cost = cap.get(5).unwrap().as_str().parse::<i32>().unwrap();
        let geode_robot_ore_cost = cap.get(6).unwrap().as_str().parse::<i32>().unwrap();
        let geode_robot_obsidian_cost = cap.get(7).unwrap().as_str().parse::<i32>().unwrap();

        let cost = Cost {
            ore: (ore_cost, 0, 0),
            clay: (clay_cost, 0, 0),
            obsidian: (obsidian_robot_ore_cost, obsidian_robot_clay_cost, 0),
            geode: (geode_robot_ore_cost, 0, geode_robot_obsidian_cost),
        };

        let initial = State::new(0, 0, 0, 0, 1, 0, 0, 0, 0);

        solve(&initial, &cost);
    }
}
