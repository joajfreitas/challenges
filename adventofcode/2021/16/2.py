import sys
from functools import reduce

class Parser():
    def __init__(self, line):
        self.pos = 0
        self.line = line

    def take(self, n):
        aux = self.line[self.pos:self.pos+n]
        self.pos += n
        return aux

class Packet():
    def __init__(self, id, version, payload, n):
        self.id = int(id, 2)
        self.version = int(version, 2)
        self.payload = payload
        self.n = n


def parse(line):
    s = ""
    for c in line:
        s += format(int(c, 16), "04b")

    return Parser(s)


def read_literal(parser):
    n = 0
    s = ""
    while True:
        subpacket = parser.take(5)
        n += 5
        s += subpacket[1:]
        if subpacket[0] == "0":
            break

    return n, int(s,2)

def read_operator(parser):
    n = 1
    ltid = parser.take(1)
    if ltid == "0":
        L = int(parser.take(15),2)
        n += 15
        packets = []
        while True:
            if L <= 0:
                return n, packets
            packet = read_packet(parser)
            n += packet.n
            packets.append(packet)
            L -= packet.n

    else:
        L = int(parser.take(11), 2)
        n += 11
        packets = []
        for i in range(L):
            packet = read_packet(parser)
            packets.append(packet)
            n += packet.n

        return n, packets

def read_packet(parser):
    version = parser.take(3)
    packet_id = parser.take(3)
    if int(packet_id,2) == 4:
        n, payload = read_literal(parser)
        return Packet(packet_id, version, payload, n+6)
    else:
        n, payload = read_operator(parser)
        return Packet(packet_id, version, payload, n+6)

def decode(parser):
    packet = read_packet(parser)
    return packet

def eval(packet):
    fs = {
        0: lambda xs: sum(xs),
        1: lambda xs: reduce(lambda x,y: x*y, [1] + xs),
        2: lambda xs: min(xs),
        3: lambda xs: max(xs),
        4: lambda xs: xs[0],
        5: lambda xs: 1 if xs[0] > xs[1] else 0,
        6: lambda xs: 1 if xs[0] < xs[1] else 0,
        7: lambda xs: 1 if xs[0] == xs[1] else 0
    }

    f = fs[packet.id]
    if isinstance(packet.payload, list):
        args = [eval(p) for p in packet.payload]
    else:
        args = [packet.payload]

    return f(args)



with open(sys.argv[1]) as f:
    lines = [line.strip() for line in f.readlines()]

for line in lines:
    print(eval(decode(parse(line))))
