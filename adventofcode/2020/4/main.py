import sys

with open(sys.argv[1]) as f:
    input = f.read()

sp = input.split("\n\n")
passports = []
for passport in sp:
    aux = {}
    for line in passport.split("\n"):
        for field in line.split(" "):
            if field == '':
                continue
            key, value = field.split(":")
            aux[key] = value

    passports.append(aux)

def check(passport):

    def fields_rule(passport):
        if len(passport.keys()) == 8:
            return True
        elif len(passport.keys()) == 7 and 'cid' not in passport.keys():
            return True
        else:
            return False

    def byr_rule(passport):
        byr = passport.get('byr')
        l = len(byr) == 4
        byr = int(byr)
        r = byr >= 1920 and byr <=2002
        return r and l

    def iyr_rule(passport):
        iyr = passport.get("iyr")
        l = len(iyr) == 4
        iyr = int(iyr)
        r = iyr >= 2010 and iyr <= 2020
        return l and r

    def eyr_rule(passport):
        eyr = passport.get("eyr")
        l = len(eyr) == 4
        eyr = int(eyr)
        r = eyr >= 2020 and eyr <= 2030
        return l and r

    def hgt_rule(passport):
        hgt = passport.get("hgt")
        unit = hgt[-2:]
        if unit not in ["cm", "in"]:
            return False
        value = float(hgt[:-2])
        if unit == 'cm':
            l = value >= 150 and value <= 193
        else:
            l = value >= 59 and value <= 76

        return l

    def hcl_rule(passport):
        hcl = passport.get("hcl")
        if hcl[0]!="#":
            return False

        value = hcl[1:]
        if len(value) != 6:
            return False

        try:
            int(hcl[1:], 16)
        except Exception as e:
            return False

        return True

    def ecl_rule(passport):
        ecl = passport.get("ecl")
        return ecl in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]

    def pid_rule(passport):
        pid = passport.get("pid")
        return len(pid) == 9

    rules = [fields_rule, byr_rule, iyr_rule, eyr_rule, hgt_rule, hcl_rule, ecl_rule, pid_rule]

    for rule in rules:
        if not rule(passport):
            return False

    return True

print(len(list(filter(check, passports))))
