#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>

class HatRack {
public:

typedef long long int64;
static const int MAXN = 54;

int n;
std::vector<int> e[MAXN];

enum subt_rack { IRREGULAR = 0, COMPLETE, FULL } result[MAXN];
typedef std::pair<enum subt_rack, int> subtree;

enum subt_rack parse_subtrees(int depth, std::vector<subtree> &children) {
    if ((int)children.size() >= 3) return IRREGULAR;
    if (depth == 1) return FULL;
    if (depth == 2) return (int)children.size() == 2 ? FULL : COMPLETE;
    if ((int)children.size() <= 1) return IRREGULAR;

    int count[3] = { 0, 0, 0 };
    for (auto t : children) ++count[t.first];
    if (count[IRREGULAR] > 0 || count[COMPLETE] == 2 || (count[COMPLETE] && !count[FULL]))
        return IRREGULAR;

    assert(count[COMPLETE] <= 1);
    std::sort(children.begin(), children.end());
    if (children[0].first == FULL) switch (children[1].second - children[0].second) {
        case 1: return COMPLETE;
        case 0: return FULL;
        default: return IRREGULAR;
    } else switch (children[1].second - children[0].second) {
        case 0: case -1: return COMPLETE;
        default: return IRREGULAR;
    }
}

int depth[MAXN];
void dfs_check(int u, int p) {
    std::vector<subtree> children;
    depth[u] = 0;
    for (int v : e[u]) if (v != p) {
        dfs_check(v, u);
        children.push_back({ result[v], depth[v] });
        if (depth[u] < depth[v]) depth[u] = depth[v];
    }
    result[u] = parse_subtrees(++depth[u], children);
}

inline int64 rooter(int r) {
    dfs_check(r, -1);
    //printf("Rooter %d\n", r + 1);
    //for (int i = 0; i < n; ++i) printf("%d %d\n", i + 1, result[i]);
    if (result[r] == IRREGULAR) return 0;
    int64 ans = 1;
    for (int i = 0; i < n; ++i) if (result[i] == FULL && depth[i] > 1) ans <<= 1;
    return ans;
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
    printf("%lld\n", worker.countWays({1}, {2}));
    printf("%lld\n", worker.countWays({1,1}, {2,3}));
    printf("%lld\n", worker.countWays({1,1,1,1}, {2,3,4,5}));
    printf("%lld\n", worker.countWays({1,1,2,2,11,11,8,8,3,3,4,4,5}, {2,3,11,8,12,13,9,10,4,5,7,6,14}));

    puts("===");
    printf("%lld\n", worker.countWays(  {3, 1}, {2, 2}));
    printf("%lld\n", worker.countWays(  {2, 1, 3}, {4, 4, 2}));
    printf("%lld\n", worker.countWays(  {1, 5, 3, 2}, {4, 4, 1, 1}));
    printf("%lld\n", worker.countWays(  {1, 4, 2, 3, 5}, {5, 3, 5, 6, 6}));
    printf("%lld\n", worker.countWays(  {6, 2, 5, 1, 3, 7}, {5, 7, 4, 5, 7, 4}));
    printf("%lld\n", worker.countWays(  {8, 6, 5, 4, 7, 2, 1}, {1, 3, 6, 6, 5, 1, 3}));
    printf("%lld\n", worker.countWays(  {3, 9, 4, 7, 6, 8, 5, 2}, {7, 1, 5, 9, 5, 9, 1, 7}      ));
    printf("%lld\n", worker.countWays(  {8, 3, 6, 5, 1, 9, 7, 2, 4}, {1, 1, 10, 7, 10, 4, 6, 4, 6}));
    printf("%lld\n", worker.countWays(  {11, 4, 8, 6, 7, 2, 1, 9, 10, 3}, {1, 11, 11, 9, 2, 5, 5, 1, 9, 2}));
    printf("%lld\n", worker.countWays(  {6, 9, 7, 8, 12, 4, 1, 10, 3, 2, 11}, {3, 1, 10, 3, 2, 5, 5, 4, 4, 1, 10}));

    puts("===");
    printf("%lld\n", worker.countWays(  {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51}));
    printf("%lld\n", worker.countWays(  {1, 1, 2, 2, 3, 3, 4, 4, 6, 6}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
    printf("%lld\n", worker.countWays(  {1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
    printf("%lld\n", worker.countWays(  {1, 3}, {2, 1}));
    printf("%lld\n", worker.countWays(  {1, 2, 3, 4}, {2, 3, 4, 5}));
    return 0;
}
