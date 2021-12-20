import sys

with open(sys.argv[1]) as f:
    algo, image = f.read().split("\n\n")

algo = algo.strip()

def get_pixel(image, algo, x,y,w,h, n):
    #print(x,y,w,h)
    if x<0 or y<0 or x>=w or y>=h:
        if algo[0] == ".":
            return "."
        else:
            return "." if n%2 ==0 else "#"
    else:
        return image[x][y]

def neighbors(image, algo, x, y, w, h, n):
    for i in range(-1,2):
        for j in range(-1,2):
            yield get_pixel(image, algo, x+i, y+j, w, h, n)

def enhance(image, algo, n):
    image = image[:-1].split("\n")
    output = ""
    w,h = len(image), len(image[0])
    for i in range(-1, w+1):
        for j in range(-1, h+1):
            idx = int("".join(neighbors(image, algo, i, j, w, h, n)).replace("#", "1").replace(".", "0"),2)
            output += algo[idx]
        output += "\n"

    return output

output = image
for i in range(50):
    output = enhance(output, algo, i)
    #print(output)
    print(output.count("#"))
