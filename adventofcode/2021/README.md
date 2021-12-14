# Advent of Code 2021

[Advent of Code 2021](https://adventofcode.com/2021/)

This year we are using python.

## benchmark

This year's goal: stay below 1s of total runtime.

Run the benchmark.py script to gather simple statistics of the runtime of each
solution. The first argument is the number of iterations of each solution to
run, a bigger number should output a more representative value but it will take
longer.

`python benchmark.py <iterations>`

Example output
```
 -> python benchmark.py 10

01-1: 13.89ms, 1390
01-2: 14.22ms, 1457
02-1: 13.4ms, 1890 1172 2215080
02-2: 13.48ms, 1890 986622 1864715580
03-1: 14.79ms, 784 3311 2595824
03-2: 13.94ms, 781 2734
04-1: 26.21ms, 6592
04-2: 39.66ms, 31755
05-1: 80.57ms, 16518
05-2: 81.21ms, 16518
06-1: 13.1ms, 353274
06-2: 13.12ms, 353274
07-1: 14.39ms, 342 351901
07-2: 21.0ms, 101079891, 101079875
08-1: 13.38ms, 548
08-2: 17.21ms, 1074888
09-1: 15.25ms, 444
09-2: 46.52ms, 1168440
10-1: 13.94ms, 367227
10-2: 14.67ms, 3583341858
11-1: 20.03ms, 1673
11-2: 28.13ms,
12-1: 38.8ms, 5874
12-2: 1134.44ms, 153592
13-1: 22.51ms, 669
13-2: 22.5ms, #..#.####.####.####..##..#..#..##....###..#.#....#.......#.#..#.#..#.#..#....##..#.###..###....#..#....#..#.#.......##..#.#....#.....#...#....#..#.#.......##..#.#....#....#....#..#.#..#.#..#.#..#.##..####.#....####..##...##...##...##.
14-1: 19.67ms, 2223
14-2: 14.05ms, 2223
=====================================
total run time for part1: 319.93ms
total run time for part2: 1474.16ms
total run time: 1794.09ms

Fastest for part1: 6:13.1ms
Fastest for part2: 6:13.12ms
Fastest day: 6:26.22ms

Slowest for part1: 5:80.57ms
Slowest for part2: 12:1134.44ms
Slowest day: 12:1173.24ms
```
