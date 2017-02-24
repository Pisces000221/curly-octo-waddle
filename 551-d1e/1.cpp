#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class ColorfulChocolates {
public:

static const int MAXN = 52;
static const int ALPHABET = 27;

int maximumSpread(std::string chocolates, int maxSwaps) {
    std::vector<int> occ[ALPHABET];
    for (int i = 0; i < (int)chocolates.length(); ++i)
        occ[chocolates[i] - 'A'].push_back(i);

    int ans = 0, cur;
    for (int ch = 0; ch < ALPHABET; ++ch) {
        for (int i = 0; i < (int)occ[ch].size(); ++i)
            for (int j = i; j < (int)occ[ch].size(); ++j) {
                cur = 0;
                for (int k = i; k <= j; ++k)
                    cur += std::abs(occ[ch][(i + j) / 2] - ((i + j) / 2 - k) - occ[ch][k]);
                if (cur <= maxSwaps && ans < (j - i + 1)) ans = (j - i + 1);
            }
    }

    return ans;
}

};

int main()
{
    ColorfulChocolates worker;
    printf("%d\n", worker.maximumSpread("ABCDCBC", 1));
    printf("%d\n", worker.maximumSpread("ABCDCBC", 2));
    printf("%d\n", worker.maximumSpread("ABBABABBA", 3));
    printf("%d\n", worker.maximumSpread("ABBABABBA", 4));
    printf("%d\n", worker.maximumSpread("QASOKZNHWNFODOQNHGQKGLIHTPJUVGKLHFZTGPDCEKSJYIWFOO", 77));
    return 0;
}
