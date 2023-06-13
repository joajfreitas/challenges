import subprocess
import time
import sys
from functools import reduce

days = {
        "01": ([], []), 
        "02": ([], []), 
        "03": ([], []), 
        "04": ([], []), 
        "05": ([], []), 
        "06": ([], []), 
        "07": ([], []), 
        "08": ([], []), 
        "09": ([], []), 
        "10": ([], []), 
        "11": ([], []), 
        "12": ([], []), 
        "13": ([], []), 
        "14": ([], []), 
        "21": ([], []), 
        "22": ([], []), 
        "25": ([], []), 
}

def build(day, part):
    print(day)
    r = subprocess.run(['cargo', 'build', '--release'], cwd=f'rust{day}-part{part}')

def benchmark(day,part, args,runs):
    mean = 0

    for i in range(runs):
        start = time.perf_counter()
        r = subprocess.run([f'rust{day}-part{part}/target/release/rust{day}-part{part}', f'rust{day}-part{part}/input'] + args1, capture_output=True)
        if r.returncode != 0:
            print("failed")
            sys.exit(1)
        output = r.stdout.decode("utf-8").replace("\n", "")
        end = time.perf_counter()
        mean += end-start

    return mean/runs, output

runs = int(sys.argv[1] or 10)
times = []

for day in days.keys():
    build(day,1)
    build(day,2)

for day, args in days.items():
    args1, args2 = args

    t1, output = benchmark(day,1,args1,runs)
    t = str(round(1000*t1,2)) + "ms"
    print(f"{day}-1: {t}, {output}")

    t2, output = benchmark(day,2,args2,runs)
    t = str(round(1000*t2,2)) + "ms"
    print(f"{day}-2: {t}, {output}")
    times.append((t1,t2))

times1 = [x for x,y in times]
times2 = [y for x,y in times]
joined_times = [x+y for x,y in times]
total1 = sum(times1) 
total2 = sum(times2)
total1 = round(1000*total1, 2)
total2 = round(1000*total2, 2)

print("=====================================")

print(f"Fastest for part1: {times1.index(min(times1))+1}:{round(1000*min(times1),2)}ms")
print(f"Fastest for part2: {times2.index(min(times2))+1}:{round(1000*min(times2),2)}ms")
print(f"Fastest day: {joined_times.index(min(joined_times))+1}:{round(1000*min(joined_times),2)}ms")

print("")

print(f"Slowest for part1: {times1.index(max(times1))+1}:{round(1000*max(times1),2)}ms")
print(f"Slowest for part2: {times2.index(max(times2))+1}:{round(1000*max(times2),2)}ms")
print(f"Slowest day: {joined_times.index(max(joined_times))+1}:{round(1000*max(joined_times),2)}ms")

print("")

print(f"total run time for part1: {total1}ms")
print(f"total run time for part2: {total2}ms")
print(f"total run time: {round(total1 + total2,2)}ms")

max = int(sys.argv[2])
if total1 + total2 > max:
    print(f"Allowed runtime exceeded max was: {max}ms, got: {round(total1+total2,2)}ms.\nYou are {round(total1+total2-max,2)}ms above the target")
    sys.exit(1)
else:
    sys.exit(0)
