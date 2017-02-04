#include <cstdio>
#include <cstring>
#include <vector>

template <typename T> inline T max(const T a, const T b) { return a > b ? a : b; }

class CentaurCompany {
public:

typedef long long int64;
static const int MAXN = 54;

int n;
std::vector<int> e[MAXN];
int64 tot = 0;
int cc = 0;
bool sel[MAXN];

void dfs_cc(int u, int p) {
    if (sel[u] && (p == -1 || !sel[p])) ++cc;
    for (int v : e[u]) if (v != p) dfs_cc(v, u);
}

double getvalue(std::vector<int> a, std::vector<int> b) {
    n = (int)a.size() + 1;
    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        e[a[i] - 1].push_back(b[i] - 1);
        e[b[i] - 1].push_back(a[i] - 1);
    }

    tot = 0;
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) sel[j] = (i >> j) & 1;
        cc = 0; dfs_cc(0, -1);
        tot += max(0, 2 * cc - __builtin_popcount(i) - 2);
        //printf("%d %d\n", i, cc);
    }

    //printf("%lld\n", tot);
    return (double)tot / (1LL << (n - 1));
}

};

int main()
{
    CentaurCompany worker;
    // 0.0, 0.125, 0.375, 0.41796875, 0.646484375
    printf("%.12lf\n", worker.getvalue({1}, {2}));
    printf("%.12lf\n", worker.getvalue({1,1,1}, {2,3,4}));
    printf("%.12lf\n", worker.getvalue({1,2,3,2,2}, {2,3,4,5,6}));  // Expected 0.375
    printf("%.12lf\n", worker.getvalue({1,2,3,4,5,6,7,8,9}, {2,3,4,5,6,7,8,9,10}));
    printf("%.12lf\n", worker.getvalue({10, 7, 2, 5, 6, 2, 4, 9, 7}, {8, 10, 10, 4, 1, 6, 2, 2, 3}));
    return 0;
}
