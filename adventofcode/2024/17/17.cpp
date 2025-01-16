#include <vector>
#include <cmath>
#include <iostream>

// b = a & 0b111
// b = b ^ 2
// c = div a b
// b = b ^ c
// b = b ^ 3
// out b
// a = div a 3
// jp 0

struct Cpu {
    Cpu(long long unsigned a, long long unsigned b, long long unsigned c) : a(a), b(b), c(c), ip(0), output{} {}
    
    long long unsigned combo(unsigned operand) {
        if (operand <= 3) {
            return operand;
        }
        else if(operand == 4) {
            return a;
        }
        else if(operand == 5) {
            return b;
        }
        else if(operand == 6) {
            return c;
        }
        else {
            throw std::runtime_error("Invalid operand");
        }
    }

    long long unsigned division(long long unsigned a, long long unsigned b) {
        return a >> b;
    }

    void step(unsigned opcode, unsigned operand) {
        if (opcode > 7) {
            throw std::runtime_error("Invalid opcode");
        }

        if (operand > 7) {
            throw std::runtime_error("Invalid operand");
        }

        if (opcode == 0) {
            a = division(a, combo(operand));
            ip += 2;
        }
        else if (opcode == 1) {
            b = b ^ operand;
            ip += 2;
        }
        else if (opcode == 2) {
            b = combo(operand) & 0x7ULL;
            ip += 2;
        }
        else if (opcode == 3) {
            if (a != 0) {
                ip = operand;
            }
            else {
                ip += 2;
            }

        }
        else if (opcode == 4) {
            b ^= c;
            ip += 2;
        }
        else if (opcode == 5) {
            output.push_back(combo(operand) & 0x7ULL);
            ip += 2;
        }
        else if (opcode == 6) {
            b = division(a, combo(operand));
            ip += 2;
        }
        else if (opcode == 7) {
            c = division(a, combo(operand));
            ip += 2;
        }
        else {
            throw std::runtime_error("Invalid opcode");
        }
    }

    void execute(std::vector<int> program) {
        while (ip < program.size()) {
            step(program[ip], program[ip + 1]);

            //std::cout << "a: " << a << " b: " << b << " c: " << c << " ip: " << ip << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        //std::cout << std::endl;
    }
    
    long long unsigned a;
    long long unsigned b;
    long long unsigned c;
    unsigned ip;
    std::vector<int> output;
};

bool check(const std::vector<int>& program, const std::vector<int>& output, int cursor) {
    for (int i=cursor, j=0; i<program.size(); i++, j++) {
        if (program[i] != output[j]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    //long long unsigned i = 35200350ULL;
    std::vector<int> example = {2,4,1,2,7,5,4,7,1,3,5,5,0,3,3,0};
    
    int cursor = example.size()-1;
    long long unsigned i = 0;
    while (true) {
        if (cursor == -1) {
            break;
        }
        for (long long unsigned j=0; j<8*8; j++) {
            auto cpu = Cpu(8*i + j, 0, 0);
            cpu.execute(example);
            if (check(example, cpu.output, cursor)) {
                for (auto z=0; z<cpu.output.size(); z++) {
                    std::cout << cpu.output[z] << " ";
                }
                std::cout << std::endl;
                i = 8*i + j;
                cursor--;
                break;
            }
        }
    }
    
    std::cout << i << std::endl;

    auto cpu = Cpu(37221274271220,0,0);
    cpu.execute(example);

    for (auto j=0; j<cpu.output.size(); j++) {
        std::cout << cpu.output[j] << " ";
    }

    //std::cout << i << std::endl;
    //for (unsigned i=0;  i< 100; i++) {
    //    
    //    for (auto j=0; j<cpu.output.size(); j++) {
    //        std::cout << cpu.output[j] << " ";
    //    }

    //    std::cout << std::endl;
    //    if (cpu.output == example){
    //        std::cout << "Found: " << i << std::endl;
    //        break;
    //    }

    //    //for (int j=0; j<cpu.output.size(); j++) {
    //    //    std::cout << cpu.output[j] << " ";
    //    //}
    //    //std::cout << std::endl;
    //    //for (int j=0; j<example.size(); j++) {
    //    //    std::cout << example[j] << " ";
    //    //}
    //    //std::cout << std::endl;
    //    //std::cout << "a: " << cpu.a << " b: " << cpu.b << " c: " << cpu.c << " ip: " << cpu.ip << std::endl;
    //}
}
