import subprocess
import time
import sys

days = {
        "01": ([], []), 
        "02": ([], []), 
        "03": ([], []), 
        "04": ([], []), 
        "05": ([], []), 
        "06": (['80'], []), 
        "07": ([], []), 
        "08": ([], []), 
        "09": ([], []), 
        "10": ([], []), 
        "11": (['100'], ['1000']),
}

runs = int(sys.argv[1] or 10)
total = 0

for day, args in days.items():
    args1, args2 = args

    mean = 0
    for i in range(runs):
        start = time.perf_counter()
        r = subprocess.run(['python', f'{day}/1.py', f'{day}/input'] + args1, capture_output=True)
        output = r.stdout.decode("utf-8").replace("\n", "")
        end = time.perf_counter()
        mean += end-start
    
    mean = mean/runs
    total += mean
    t = str(round(1000*mean,2)) + "ms"

    print(f"{day}-1: {t}, {output}")

    mean = 0
    for i in range(runs):
        start = time.perf_counter()
        r = subprocess.run(['python', f'{day}/2.py', f'{day}/input'] + args1, capture_output=True)
        output = r.stdout.decode("utf-8").replace("\n", "")
        end = time.perf_counter()
        mean += end-start
    
    mean = mean/runs
    total += mean
    t = str(round(1000*mean,2)) + "ms"

    print(f"{day}-2: {t}, {output}")

total = round(1000*total, 2)
print(f"total run time: {total}ms")

