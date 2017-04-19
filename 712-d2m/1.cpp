#include <cstdio>
#include <string>
#include <vector>

class MakePalindrome {
public:

static const int ALPHABET = 26;

std::vector<std::string> constructMinimal(std::string card) {
    int ct[ALPHABET] = { 0 };
    for (int i = 0; i < card.length(); ++i) ++ct[card[i] - 'a'];

    std::vector<std::string> ret;
    for (int i = 0; i < ALPHABET; ++i)
        if (ct[i] & 1) ret.push_back(std::string(1, i + 'a')), --ct[i];
    for (int i = 0; i < ALPHABET; ++i)
        for (int j = 0; j < ct[i]; j += 2) {
            ret[0].insert(ret[0].begin(), i + 'a');
            ret[0].insert(ret[0].end(), i + 'a');
        }

    return ret;
}

};

int main()
{
    MakePalindrome worker;
    for (auto i : worker.constructMinimal("abbaa")) printf(" %s", i.c_str()); putchar('\n');
    for (auto i : worker.constructMinimal("abc")) printf(" %s", i.c_str()); putchar('\n');
    for (auto i : worker.constructMinimal("aaabbbccc")) printf(" %s", i.c_str()); putchar('\n');
    return 0;
}
