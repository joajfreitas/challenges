#include <vector>
#include <string>
#include <map>
#include <array>



std::map<std::string, int> init_values = {
    {"x00", 1},
    {"x01", 0},
    {"x02", 1},
    {"x03", 1},
    {"x04", 0},
    {"y00", 1},
    {"y01", 1},
    {"y02", 1},
    {"y03", 1},
    {"y04", 1}
};

std::vector<std::array<std::string, 4>> chain = {
    std::array<std::string, 4>{"ntg" ,"XOR" ,"fgs", "mjb"},
    std::array<std::string, 4>{"y02", "OR"  ,"x01", "tnw"},
    std::array<std::string, 4>{"kwq", "OR"  ,"kpj", "z05"},
    std::array<std::string, 4>{"x00", "OR"  ,"x03", "fst"},
    std::array<std::string, 4>{"tgd" ,"XOR" ,"rvg", "z01"},
    std::array<std::string, 4>{"vdt", "OR"  ,"tnw", "bfw"},
    std::array<std::string, 4>{"bfw" ,"AND" ,"frj", "z10"},
    std::array<std::string, 4>{"ffh", "OR"  ,"nrd", "bqk"},
    std::array<std::string, 4>{"y00" ,"AND" ,"y03", "djm"},
    std::array<std::string, 4>{"y03", "OR"  ,"y00", "psh"},
    std::array<std::string, 4>{"bqk", "OR"  ,"frj", "z08"},
    std::array<std::string, 4>{"tnw", "OR"  ,"fst", "frj"},
    std::array<std::string, 4>{"gnj" ,"AND" ,"tgd", "z11"},
    std::array<std::string, 4>{"bfw" ,"XOR" ,"mjb", "z00"},
    std::array<std::string, 4>{"x03", "OR"  ,"x00", "vdt"},
    std::array<std::string, 4>{"gnj" ,"AND" ,"wpb", "z02"},
    std::array<std::string, 4>{"x04" ,"AND" ,"y00", "kjc"},
    std::array<std::string, 4>{"djm", "OR"  ,"pbm", "qhw"},
    std::array<std::string, 4>{"nrd" ,"AND" ,"vdt", "hwm"},
    std::array<std::string, 4>{"kjc" ,"AND" ,"fst", "rvg"},
    std::array<std::string, 4>{"y04", "OR"  ,"y02", "fgs"},
    std::array<std::string, 4>{"y01" ,"AND" ,"x02", "pbm"},
    std::array<std::string, 4>{"ntg", "OR"  ,"kjc", "kwq"},
    std::array<std::string, 4>{"psh" ,"XOR" ,"fgs", "tgd"},
    std::array<std::string, 4>{"qhw" ,"XOR" ,"tgd", "z09"},
    std::array<std::string, 4>{"pbm", "OR"  ,"djm", "kpj"},
    std::array<std::string, 4>{"x03" ,"XOR" ,"y03", "ffh"},
    std::array<std::string, 4>{"x00" ,"XOR" ,"y04", "ntg"},
    std::array<std::string, 4>{"bfw", "OR"  ,"bqk", "z06"},
    std::array<std::string, 4>{"nrd" ,"XOR" ,"fgs", "wpb"},
    std::array<std::string, 4>{"frj" ,"XOR" ,"qhw", "z04"},
    std::array<std::string, 4>{"bqk", "OR"  ,"frj", "z07"},
    std::array<std::string, 4>{"y03", "OR"  ,"x01", "nrd"},
    std::array<std::string, 4>{"hwm" ,"AND" ,"bqk", "z03"},
    std::array<std::string, 4>{"tgd" ,"XOR" ,"rvg", "z12"},
    std::array<std::string, 4>{"tnw", "OR"  ,"pbm", "gnj"}
};
