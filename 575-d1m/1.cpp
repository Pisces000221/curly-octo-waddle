#include <cstdio>
#include <string>
#include <vector>

class TheSwapsDivOne {
public:

static const int MAXN = 47 * 47 + 2;
static const int MAXK = 1e6 + 4;
int n;
int a[MAXN];
// f/g[# ops] = for a given position P, possibility to get to **one** position Q s.t. P !=/== Q
double f[MAXK], g[MAXK];

// O(n^2 + k)
// Optimization to O(n + log k) should be quite simple = =
double find(std::vector<std::string> sequence, int k) {
    n = 0;
    for (auto s : sequence) {
        for (int i = 0; i < s.length(); ++i) a[n++] = s[i] - '0';
    }

    f[0] = 0, g[0] = 1;
    for (int i = 1; i <= k; ++i) {
        f[i] = (f[i - 1] * (n * (n - 1) / 2 - 1) + g[i - 1]) / (n * (n - 1) / 2);
        g[i] = 1.0 - f[i] * (n - 1);
    }

    double ans = 0;
    for (int i = 0; i < n; ++i) {
        double cur = 0;
        for (int j = 0; j < n; ++j)
            cur += (i == j ? g[k] : f[k]) * a[j];
        ans += cur * (i + 1) * (n - i) / (n * (n + 1) / 2);
    }

    return ans;
}

};

int main()
{
    static TheSwapsDivOne worker;
    printf("%.4lf\n", worker.find({"4", "77"}, 1));
    printf("%.4lf\n", worker.find({"4", "77"}, 47));
    printf("%.4lf\n", worker.find({"1", "1", "1", "1", "1", "1", "1"}, 1000000));
    printf("%.4lf\n", worker.find({"572685085149095989026478064633266980348504469", "19720257361", "9", "69"}, 7));
    return 0;
}
