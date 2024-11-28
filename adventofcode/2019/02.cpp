#include <array>
#include <string>
#include <map>
#include <iostream>

std::tuple<bool, bool> count_letters(const std::string& line) {
    std::map<char, int> letters{};

    for (auto c: line) {
        if (auto search = letters.find(c); search == letters.end()) {
            letters[c] = 1;
        }
        else {
            letters[c]+=1;
        }
    }

    int repeat2 = 0;
    int repeat3 = 0;

    for (const auto& [key, value]: letters) {
        if (value == 2) {
            repeat2++;
        }
        else if (value == 3) {
            repeat3++;
        }
    }

    return {repeat2 > 0, repeat3 > 0};
}

int cmp(const std::string &s1, const std::string &s2) {
    int acc = 0;
    for (std::size_t i=0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) {
            acc++;
        }
    }

    return acc;
}

int main() {
    std::array<std::string, 250> data = {
        "cvfueihajytpmrdkgsxfqplbxn",
        "cbzueihajytnmrdkgtxfqplbwn",
        "cvzucihajytomrdkgstfqplqwn",
        "cvzueilajytomrdkgsxfqwnbwn",
        "cvzueihajytomrdkgsgwqphbwn",
        "wuzuerhajytomrdkgsxfqplbwn",
        "cyzueifajybomrdkgsxfqplbwn",
        "cvzueihajxtomrdkgpxfqplmwn",
        "ivzfevhajytomrdkgsxfqplbwn",
        "cvzueihajytomrdlgsxfqphbbn",
        "uvzueihajjtomrdkgsxfqpobwn",
        "cvzupihajytomrdkgsxfqplpwe",
        "cvzueihajyvomrdkgsxfqplbrl",
        "cczueihajytomrdkgsnfqpxbwn",
        "cvzueigajytdmrdkgsxyqplbwn",
        "cvzujihljytomrdkgsxuqplbwn",
        "cvzueisajytomrddgsxkqplbwn",
        "cvzneihajytomrdkgsgaqplbwn",
        "cvzueihajytomrdkgsinmplbwn",
        "cveueihajyromrdkgsxfqplown",
        "cypueihajytotrdkgzxfqplbwn",
        "cvzuoihajytomvdqgsxfqplbwn",
        "cvzuekhejytwmrdkgsxfqplbwn",
        "cvzseihajytomrdkgsxfqgmbwn",
        "cvfuhihajytomrdkgsxfqplbwi",
        "cvzueihujxtomrdkgsufqplbwn",
        "cvzueihdjytomrdogsxfqplbwh",
        "cvzueihdjyfohrdkgsxfqplbwn",
        "cvtudihajytolrdkgsxfqplbwn",
        "cvzueihajytymrdkgshzqplbwn",
        "cvzuebhajytomxdkgsxfqplbwt",
        "cvzulihajyxomrdkgsbfqplbwn",
        "cvzueihajywomrdkgsxfqplbts",
        "cvzueihajytouodkdsxfqplbwn",
        "cvzueihajytomgdkgqxfqklbwn",
        "cvzubihajytomvdkgsxfqplmwn",
        "cvhueihajyyocrdkgsxfqplbwn",
        "zvzueihajytourdkgsxflplbwn",
        "cvzbeihajytomadkgsxfoplbwn",
        "cvzueihajytomrdkgnxfqplbsl",
        "cvfueihajftkmrdkgsxfqplbwn",
        "cvzuexhajytomryugsxfqplbwn",
        "cvzueihajytomsckgsxfqalbwn",
        "cvzuexhajytomrdkbsxfqpluwn",
        "cvzueihajytbmrtkgsxwqplbwn",
        "cvzueihajytomrdigsxfqqlbsn",
        "cvzweihajytomydkgsxfmplbwn",
        "bvzteihajytimrdkgsxfqplbwn",
        "cvzueihajytpmrdkgsxfcpbbwn",
        "cvzueigsjltomrdkgsxfqplbwn",
        "cvzueihajytomrikgsxfopldwn",
        "cvzueihajstomrdkgsxfqplgon",
        "cvzueimajytomrnkxsxfqplbwn",
        "cvzleihagatomrdkgsxfqplbwn",
        "cvbueihajotomrdkgsxfqjlbwn",
        "cvzueihajytomrdkgsxfqppnvn",
        "hvzueihajytomrdkghxfkplbwn",
        "cvzueigajytxmrdkgsxfqplbjn",
        "cvzueihaaxtokrdkgsxfqplbwn",
        "cvzueihajyeomrdkgujfqplbwn",
        "cvzueiwajpoomrdkgsxfqplbwn",
        "cvzieidtjytomrdkgsxfqplbwn",
        "cvzueihalytomrakbsxfqplbwn",
        "wtzueihajytomrdkgsxfqplbwq",
        "cvzuelhaiytomrdkgsxfqplcwn",
        "cvzueihajytomrdkgsxfqslswd",
        "cvzueihajytomrykgssfqplbon",
        "cvzueihfjytovrdegsxfqplbwn",
        "cvzueihajytomldqgsxfqplbwy",
        "cvzleihjjytomrtkgsxfqplbwn",
        "cvzueihaldtomrdtgsxfqplbwn",
        "cvzueihajytzmrdkgsxfeplqwn",
        "cvzueihrjytomddkgsxfqpgbwn",
        "cyzulihajytokrdkgsxfqplbwn",
        "cvsueihajytoordfgsxfqplbwn",
        "fvzueyhajytomrdkgaxfqplbwn",
        "cczueihajytobrdkgsefqplbwn",
        "cvzueihajytomcdrgscfqplbwn",
        "cvzuexhajyvomrdkgssfqplbwn",
        "cvzsmihajyiomrdkgsxfqplbwn",
        "cvzzeihajttomrdkgsxzqplbwn",
        "cvzseihajytomrdkgsxfqpebvn",
        "cvzueihajgthmrdkgsbfqplbwn",
        "ruzueihajytomrdkgsxfqphbwn",
        "cvzueihajytofrdkgsnfrplbwn",
        "cvzuetdajytojrdkgsxfqplbwn",
        "fvzueihajytomrdkghxfqpobwn",
        "cvzueihsjytomrdkgsxfqglbxn",
        "cvzueihajytowrdkgsxfqpsbun",
        "cvzteihaiytomrdkfsxfqplbwn",
        "cvzueihajytkmrdkrsxfqplvwn",
        "cvzueihajyoomrdkasxfqjlbwn",
        "lvzurihajytkmrdkgsxfqplbwn",
        "cvzueihajyyomrdagsxfqelbwn",
        "cvfueihajytomrdkgsxfqplbbx",
        "cvwueihajytommdkgkxfqplbwn",
        "cvzucicajytomrdkgsxcqplbwn",
        "dvzueihahytgmrdkgsxfqplbwn",
        "cvzuechajytomrdkgsxfqelwwn",
        "cvzuekhajytomrdkgsxknplbwn",
        "cvtueihajytomphkgsxfqplbwn",
        "cvzueihabytnzrdkgsxfqplbwn",
        "cvzusihajytomrdkgfxfqplban",
        "cvfueihajytomcdfgsxfqplbwn",
        "mvzueihapytomrdkgsxfdplbwn",
        "cvzueihajytomhdkgsxmqppbwn",
        "jvsueihajytomrdkgsxfqplbln",
        "cvzujihajybomrdkgsxtqplbwn",
        "cvzuekhawytomrdkgsxfqplbwc",
        "svzueihanytomrdogsxfqplbwn",
        "cvzujihajytodrdkgslfqplbwn",
        "cvgdeihajytorrdkgsxfqplbwn",
        "cvzbeihajytoprdkgsxfqplbyn",
        "cvzueihkyytomjdkgsxfqplbwn",
        "cvzuelhojytomrdkgsxfqjlbwn",
        "evzueihajytimrdkgsxfqpsbwn",
        "cvzueihajydomrdkjsxfqplbjn",
        "ovzteihajytosrdkgsxfqplbwn",
        "cvzueihajyaomrdzgsxfqplbgn",
        "cvzuewhajmtomrdkgsufqplbwn",
        "cvzueihajqtomhukgsxfqplbwn",
        "cvzueihajytomzqkgsxfqplbwk",
        "cazuewhakytomrdkgsxfqplbwn",
        "clzueihatytomrdkgzxfqplbwn",
        "dvzueihajytomqdkgsxfqpnbwn",
        "cvzueidajdtomrdkgsxtqplbwn",
        "cvzueihabytowrdkgsxoqplbwn",
        "cvzujihwjytomrdkgsxeqplbwn",
        "cvtuedhajytomrdkgsxfqplbbn",
        "cvzueihajcgomrdkgsxfqplswn",
        "cvzuephajyiomrdngsxfqplbwn",
        "cvzueihajythmqdkgsxfqplbwf",
        "cvzueitajytomrdkgsxfepvbwn",
        "cvzueihajytomydkgsxfqplvwb",
        "dvzueshajytomrddgsxfqplbwn",
        "cvzueihajytomrdkgvxfqpwben",
        "cvzueihajytomrdkgvxfpplwwn",
        "cvzuefhajftomrdkgsxfqrlbwn",
        "cvzueihajytpmrvkgsxfqplbcn",
        "cvzueihajytohrdkgsxfqxnbwn",
        "cvzueihajytomrdposxfqulbwn",
        "cozueihajytomrpkgsxfqrlbwn",
        "cvzuuihaxytomrdkgsxfqplbtn",
        "cvzueihajytomrbzgsxyqplbwn",
        "cveueihajyxoqrdkgsxfqplbwn",
        "cvzueihajytomrkkgsxfqptbrn",
        "cvzuezhajatomrdkssxfqplbwn",
        "cpzueihajytomrdkgsxfhplbwo",
        "lviueihajytomrekgsxfqplbwn",
        "cvzueihwjytomrdkusxfyplbwn",
        "cvzgeihajytomwdkgsxfrplbwn",
        "cvzsejhzjytomrdkgsxfqplbwn",
        "cvzuuihajytomrdkgsxfqdlbwz",
        "cvzjeihajytomrdugsxftplbwn",
        "cvzueihaxytomrrkgsxfmplbwn",
        "cvzueihajgtomrdhgsxfqplwwn",
        "cvzulihajytomedkgsxfqplewn",
        "cvzueivajytomrdkmsxfqplbwc",
        "cvzuervajytomrdkgsxfwplbwn",
        "cvzuemhcjytomrdkgslfqplbwn",
        "cvzyerhauytomrdkgsxfqplbwn",
        "cvzueihaoytomrdkgsyfqplewn",
        "cvzueihanytomrdkgsafkplbwn",
        "cvzueihajvtomrdugsxfqpcbwn",
        "chzueihajytamrdxgsxfqplbwn",
        "cvzueihalytomrdsgsxfqplbln",
        "cvzueihajytoyaykgsxfqplbwn",
        "tlzueihajyeomrdkgsxfqplbwn",
        "cvpueihajytbmrdkgsxfxplbwn",
        "cvzueihajytomjdkgsxuqplkwn",
        "cvzueihajygomrdkgkxfqplbwg",
        "cvzueihajhtomrdkgbxsqplbwn",
        "cvzurihajytomrdkgsafqplbwx",
        "cdzuezhajytomrdkgsxrqplbwn",
        "cvbueihajytotrwkgsxfqplbwn",
        "cwzkeihajytomrdkgsxfqplbwh",
        "cvzheihajytolrikgsxfqplbwn",
        "cozuevhajytomrdkgkxfqplbwn",
        "chzueihajytomrjkgsxfqulbwn",
        "cvzueihkjyromrdkgsxvqplbwn",
        "cvzveihajytomrdkgsxpqplnwn",
        "cvzueihajytoirdkgsxfqihbwn",
        "cvoueihajytomrdkgsxfqpdawn",
        "pvzueihajytomrdkgnxfqplbfn",
        "cvzueihakytomxdkgssfqplbwn",
        "cvzueivajytomrdbgsxaqplbwn",
        "cvzueihajytokrdkgszrqplbwn",
        "cvzuevhajytomrdkgsxgqplbwi",
        "cvzueihajylomrdkgsxflplbpn",
        "hvzueihajytomvdkgsxfqplgwn",
        "cvzleihajytymrrkgsxfqplbwn",
        "crzueieajytomrdkgsxfqplbon",
        "cszueihajytomrdlgqxfqplbwn",
        "cvzueihacytomrdkgsxfjblbwn",
        "cvzreihajytomrdkgsxfqplzun",
        "cvzurihajytomrdkgsxiqplawn",
        "uvzueihajyhovrdkgsxfqplbwn",
        "cvzueihajyqodrdkgssfqplbwn",
        "cvzwiihrjytomrdkgsxfqplbwn",
        "cqzueihajytomrdkgjxfqplban",
        "cvmueihajytoordkgsxfqplbyn",
        "cypueihajytomrdkgzxfqplbwn",
        "cvzueihajykomrdkgsmfqplbtn",
        "cvzueidajytimrdkgsxfqpdbwn",
        "cvzheihajytomrdkgsxfqpfewn",
        "dvzueihajytumrdzgsxfqplbwn",
        "cvzueixajytomrdkgsvfqplgwn",
        "cvzuevhzjyzomrdkgsxfqplbwn",
        "cvyeeihajytomrdkgsxnqplbwn",
        "cvzueihajytomrdkggtpqplbwn",
        "cvzceiyajytomrdkgexfqplbwn",
        "cvzuelhajyyomrdkzsxfqplbwn",
        "cvzhzihajygomrdkgsxfqplbwn",
        "cvzueihwjytomrdkgsgfqplbrn",
        "cvzsevhajytomrdkgqxfqplbwn",
        "cvzueiuajytomrdkgsxfppebwn",
        "nvzueihajytemrdkgsxwqplbwn",
        "cvzueihajytocgdkgsxfqvlbwn",
        "cczusihajytomrdkgsxfqplbpn",
        "cmzueihajytomrdkbsxwqplbwn",
        "cvzumfdajytomrdkgsxfqplbwn",
        "cvzueihcjytomrdkgsxfqplbkl",
        "cvzueihajytomawknsxfqplbwn",
        "kvzueihijytomrdkgsxdqplbwn",
        "cdzutihajytomrdkgsxfkplbwn",
        "cvzufihadylomrdkgsxfqplbwn",
        "cvzueihajytomrgkxsxfqphbwn",
        "cvzuewhajyzomrdkgsxfqelbwn",
        "cvzueihajytomrdkgqxfqelbwc",
        "cvzueshajyoomrdkgsxfqflbwn",
        "cvzueihajyromrekgixfqplbwn",
        "chzugihajytomrdkgsxfqplawn",
        "cvzueihajytomrdkgsxfhpmbwy",
        "cvzueihacytodxdkgsxfqplbwn",
        "cvzurihajytourdkgsdfqplbwn",
        "cvzzeihmjytomrddgsxfqplbwn",
        "cvzucyhajygomrdkgsxfqplbwn",
        "ckzueihzjytomrdkgsxwqplbwn",
        "cvlueihajmtozrdkgsxfqplbwn",
        "cvzkeihajytomrdkgsxfqclbwc",
        "cvzueihajytomrdkgsxgdplbwa",
        "cvzueihyjytoxrdkgcxfqplbwn",
        "cvzueizavytomfdkgsxfqplbwn",
        "cvzueihajwtosrdkgsxfqllbwn",
        "cvzueihajytomrdaksxfqpllwn",
        "cvzuuihojytombdkgsxfqplbwn",
        "cvzuiibajytpmrdkgsxfqplbwn",
        "cvzueihajyuomydkgsxfqplzwn",
        "cvzueihajytimrmkgsxfqplfwn",
        "cvzueihajytomrdkgzxfqpljwo"
    };
    
    int repeat2 = 0;
    int repeat3 = 0;

    for (const auto& line: data) {
        auto [repeat2_, repeat3_] = count_letters(line);
        repeat2 += repeat2_ ? 1 : 0;
        repeat3 += repeat3_ ? 1 : 0;
    }
    
    std::cout << repeat2 * repeat3 << std::endl;

    for (std::size_t i=0; i<data.size(); i++) {
        for (std::size_t j=0; j<data.size(); j++) {
            if (cmp(data[i], data[j]) == 1) {
                std::cout << data[i] << std::endl;
                std::cout << data[j] << std::endl;
                return 0;
            }
        }
    }
    return 0;
}
