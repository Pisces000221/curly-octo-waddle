#include <cstdio>
#include <cstring>
#include <vector>

class HatRack {
public:

typedef long long int64;
static const int MAXN = 54;

int n;
std::vector<int> e[MAXN];

bool valid;
int ct_1ch, ct_stfull;
int max_d, sts[MAXN], d[MAXN], d_sz[MAXN];
void dfs_dist(int u, int p, int depth) {
    sts[u] = 1;
    d[u] = depth; ++d_sz[depth];
    if (max_d < depth) max_d = depth;
    int children = 0;
    for (int v : e[u]) if (v != p) children++, dfs_dist(v, u, depth + 1), sts[u] += sts[v];
    if (sts[u] > 1 && __builtin_popcount(sts[u] + 1) == 1) ++ct_stfull;
    if (children > 2) valid = false;
    else if (children == 1 && (++ct_1ch) >= 2) valid = false;
}

inline int64 rooter(int r) {
    //printf("Rooter %d\n", r);
    ct_1ch = ct_stfull = 0; max_d = -1;
    memset(d_sz, 0, sizeof d_sz);
    valid = true; dfs_dist(r, -1, 0);
    if (!valid) return 0;
    //for (int i = 0; i <= max_d; ++i) printf("%d %d\n", i, d_sz[i]);
    for (int i = 0; i < max_d; ++i)
        if (d_sz[i] != (1 << i)) return 0;
    //if (d_sz[max_d] % 2 == 0) return (1 << (n / 2));
    //else return (1 << (n / 2 - max_d));
    return (1 << ct_stfull);
}

int64 countWays(std::vector<int> knob1, std::vector<int> knob2) {
    n = (int)knob1.size() + 1;
    if (n <= 2) return n;

    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        e[knob1[i] - 1].push_back(knob2[i] - 1);
        e[knob2[i] - 1].push_back(knob1[i] - 1);
    }

    int64 ans = 0;
    for (int i = 0; i < n; ++i) if ((int)e[i].size() == 2) ans += rooter(i);

    return ans;
}

};

int main()
{
    HatRack worker;
    /*printf("%lld\n", worker.countWays({1}, {2}));
    printf("%lld\n", worker.countWays({1,1}, {2,3}));
    printf("%lld\n", worker.countWays({1,1,1,1}, {2,3,4,5}));
    printf("%lld\n", worker.countWays({1,1,2,2,11,11,8,8,3,3,4,4,5}, {2,3,11,8,12,13,9,10,4,5,7,6,14}));*/

    /*puts("===");
    printf("%lld\n", worker.countWays(  {3, 1}, {2, 2}));
    printf("%lld\n", worker.countWays(  {2, 1, 3}, {4, 4, 2}));
    printf("%lld\n", worker.countWays(  {1, 5, 3, 2}, {4, 4, 1, 1}));
    printf("%lld\n", worker.countWays(  {1, 4, 2, 3, 5}, {5, 3, 5, 6, 6}));
    printf("%lld\n", worker.countWays(  {6, 2, 5, 1, 3, 7}, {5, 7, 4, 5, 7, 4}));
    printf("%lld\n", worker.countWays(  {8, 6, 5, 4, 7, 2, 1}, {1, 3, 6, 6, 5, 1, 3}));
    printf("%lld\n", worker.countWays(  {3, 9, 4, 7, 6, 8, 5, 2}, {7, 1, 5, 9, 5, 9, 1, 7}      ));
    printf("%lld\n", worker.countWays(  {8, 3, 6, 5, 1, 9, 7, 2, 4}, {1, 1, 10, 7, 10, 4, 6, 4, 6}));
    printf("%lld\n", worker.countWays(  {11, 4, 8, 6, 7, 2, 1, 9, 10, 3}, {1, 11, 11, 9, 2, 5, 5, 1, 9, 2}));
    printf("%lld\n", worker.countWays(  {6, 9, 7, 8, 12, 4, 1, 10, 3, 2, 11}, {3, 1, 10, 3, 2, 5, 5, 4, 4, 1, 10}));*/

    puts("===");
    //printf("%lld\n", worker.countWays(  {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51}));
    printf("%lld\n", worker.countWays(  {1, 1, 2, 2, 3, 3, 4, 4, 6, 6}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
    //printf("%lld\n", worker.countWays(  {1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
    //printf("%lld\n", worker.countWays(  {1, 3}, {2, 1}));
    //printf("%lld\n", worker.countWays(  {1, 2, 3, 4}, {2, 3, 4, 5}));
    return 0;
}
