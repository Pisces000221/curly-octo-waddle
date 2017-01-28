#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <vector>

class KingdomAndDice {
public:

static const int MAXN = 52;

double newFairness(std::vector<int> d1, std::vector<int> d2, int num_range) {
    int n = (int)d1.size();

    std::sort(d1.begin(), d1.end());
    std::sort(d2.begin(), d2.end());
    int zero_ct = 0;
    zero_ct = std::distance(d1.begin(), std::upper_bound(d1.begin(), d1.end(), 0));

    std::vector<int> contrib;
    int last_d2 = 0, less_d2 = 0;
    d2.push_back(num_range + 1);
    for (int val : d2) {
        int count = std::min<int>(zero_ct,
            val - last_d2 - 1 - std::distance(
                std::upper_bound(d1.begin(), d1.end(), last_d2),
                std::lower_bound(d1.begin(), d1.end(), val)));
        for (int i = 0; i < count; ++i) contrib.push_back(less_d2);
        //printf("%d(%d) %d\n", val, less_d2, count);
        last_d2 = val; ++less_d2;
    }
    //for (int val : contrib) printf(" %d", val); putchar('\n');

    int base = 0;
    for (int val : d1)
        if (val) base += std::distance(d2.begin(), std::lower_bound(d2.begin(), d2.end(), val));

    static bool f[MAXN][MAXN * MAXN];
    std::fill(&f[0][0], &f[0][0] + sizeof f / sizeof f[0][0], false);
    f[0][0] = true;
    for (int val : contrib) {
        for (int i = zero_ct - 1; i >= 0; --i)
            for (int j = n * n - val; j >= 0; --j)
                if (f[i][j]) f[i + 1][j + val] = true;
    }
    //printf("%d %d\n", base, n * n);

    std::pair<int, int> ans = { n * n, 0 };
    for (int i = 0; i <= zero_ct; ++i)
        for (int j = 0; j <= n * n; ++j) if (f[i][j])
            ans = std::min(ans, std::make_pair(std::abs(2 * (j + base) - n * n), j + base));
    return (double)ans.second / (n * n);
}

};

int main()
{
    KingdomAndDice worker;
    printf("%.4lf\n", worker.newFairness({0, 2, 7, 0}, {6, 3, 8, 10}, 10));
    printf("%.4lf\n", worker.newFairness({0, 0}, {5, 8}, 47));
    printf("%.4lf\n", worker.newFairness({19, 50, 4}, {26, 100, 37}, 1000));
    std::vector<int> a, b;
    for (int i = 0; i < 50; ++i) a.push_back(rand() % 2 == 0 ? 0 : rand() % 100000 + 1);
    for (int i = 0; i < 50; ++i) b.push_back(rand() % 100000 + 1);
    printf("%.4lf\n", worker.newFairness(a, b, 1000000));
    return 0;
}
