#include <cstdio>
#include <algorithm>
#include <vector>

class SpellCards {
public:

static const int MAXN = 53;

int maxDamage(std::vector<int> level, std::vector<int> damage) {
    int n = level.size();

    int f[MAXN] = { 0 };
    for (int i = 0; i < n; ++i) {
        for (int j = n - level[i]; j >= 0; --j)
            f[j + level[i]] = std::max(f[j + level[i]], f[j] + damage[i]);
    }

    return *std::max_element(f, f + n + 1);
}

};

int main()
{
    SpellCards worker;
    printf("%d\n", worker.maxDamage({1,1,1}, {10,20,30}));
    printf("%d\n", worker.maxDamage({50,1,50,1,50}, {10,20,30,40,50}));
    printf("%d\n", worker.maxDamage({1,2,2,3,1,4,2}, {113,253,523,941,250,534,454}));
    return 0;
}
