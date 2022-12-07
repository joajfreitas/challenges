# Advent of Code 2022

[Advent of Code 2022](https://adventofcode.com/2022/)

This year we are using rust.

## benchmark

This year's goals: 
 * Get 50 stars with solutions in rust
 * Stay below 1s of total runtime

Run the rust_benchmark.py script to gather simple statistics of the runtime of each
solution. The first argument is the number of iterations to run for each
solution, the result is taken from the average of those runs.

`python rust_benchmark.py <iterations> <max allowed time in ms>`

Example output
```
 -> python rust_benchmark.py 10 1000

01-1: 0.56ms, max: 69626
01-2: 0.51ms, sum: 206780
02-1: 0.68ms, 10404
02-2: 0.61ms, 10334
03-1: 0.71ms, 7875
03-2: 0.75ms, 2479
04-1: 0.59ms, 528
04-2: 0.59ms, 881
05-1: 0.97ms, WCZTHTMPS
05-2: 0.97ms, BLSGJSDTS
06-1: 0.47ms, 1707
06-2: 0.51ms, 3697
07-1: 1.33ms, 2104783
07-2: 1.33ms, 5883165
=====================================
Fastest for part1: 6:0.47ms
Fastest for part2: 6:0.51ms
Fastest day: 6:0.98ms

Slowest for part1: 7:1.33ms
Slowest for part2: 7:1.33ms
Slowest day: 7:2.66ms

total run time for part1: 5.32ms
total run time for part2: 5.28ms
total run time: 10.6ms
```
