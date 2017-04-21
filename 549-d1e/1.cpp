#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

namespace nwf {

static const int MAXN = 105;
static const int MAXM = 53 * 53 * 2;
static const int INF = 0x3fffffff;

int n, m, source, sink;
int head[MAXN], dest[MAXM], cap[MAXM], next[MAXM];

inline void init(int _n) { n = _n, m = 0; for (int i = 0; i < n; ++i) head[i] = -1; }
inline void add_edge(int u, int v, int w) {
    dest[m] = v; cap[m] = w; next[m] = head[u]; head[u] = m++;
    dest[m] = u; cap[m] = 0; next[m] = head[v]; head[v] = m++;
}

int d[MAXN];
inline bool level_graph() {
    memset(d, -1, sizeof d);
    static int q[MAXN], qhead, qtail;
    q[0] = source, qhead = 0, qtail = 1, d[source] = 0;
    while (qhead < qtail) {
        int u = q[qhead++];
        for (int w = head[u]; w != -1; w = next[w]) if (cap[w] > 0 && d[dest[w]] == -1) {
            d[dest[w]] = d[u] + 1;
            q[qtail++] = dest[w];
        }
    }
    return d[sink] > 0;
}

int cur[MAXN];
inline int augment(int u, int cur_cap) {
    if (u == sink) return cur_cap;
    int new_cap;
    for (int &w = cur[u]; w != -1; w = next[w])
        if (cap[w] > 0 && d[dest[w]] == d[u] + 1
            && (new_cap = augment(dest[w], std::min(cur_cap, cap[w])) > 0))
        {
            cap[w] -= new_cap;
            cap[w ^ 1] += new_cap;
            return new_cap;
        }
    return 0;
}

inline int deluge() {
    int ans = 0, aug;
    while (level_graph()) {
        for (int i = 0; i < n; ++i) cur[i] = head[i];
        while ((aug = augment(source, INF)) > 0) ans += aug;
    }
    return ans;
}

}

class PointyWizardHats {
public:

int getNumHats(std::vector<int> topHeight, std::vector<int> topRadius, std::vector<int> bottomHeight, std::vector<int> bottomRadius) {
    int top_n = topHeight.size(), bottom_n = bottomHeight.size();
    nwf::init(top_n + bottom_n + 2);
    nwf::source = top_n + bottom_n;
    nwf::sink = top_n + bottom_n + 1;
    for (int i = 0; i < top_n; ++i) nwf::add_edge(nwf::source, i, 1);
    for (int i = 0; i < bottom_n; ++i) nwf::add_edge(i + top_n, nwf::sink, 1);
    for (int i = 0; i < top_n; ++i)
        for (int j = 0; j < bottom_n; ++j)
            if (topHeight[i] * bottomRadius[j] > topRadius[i] * bottomHeight[j] && topRadius[i] < bottomRadius[j])
                nwf::add_edge(i, j + top_n, 1);
    return nwf::deluge();
}

};

int main()
{
    PointyWizardHats worker;
    printf("%d\n", worker.getNumHats({30}, {3}, {3}, {30}));
    printf("%d\n", worker.getNumHats({4,4}, {4,3}, {5,12}, {5,4}));
    printf("%d\n", worker.getNumHats({3}, {3}, {1,1}, {2,4}));
    printf("%d\n", worker.getNumHats({10,10}, {2,5}, {2,9}, {3,6}));
    printf("%d\n", worker.getNumHats({3,4,5}, {5,4,3}, {3,4,5}, {3,8,5}));
    printf("%d\n", worker.getNumHats({1,2,3,4,5}, {2,3,4,5,6}, {2,3,4,5,6}, {1,2,3,4,5}));
    printf("%d\n", worker.getNumHats({123,214,232,323,342,343}, {123,123,232,123,323,434}, {545,322,123,545,777,999}, {323,443,123,656,767,888}));
    printf("%d\n", worker.getNumHats({999,999,999,10000,10000,10000}, {10000,10000,10000,1,2,3}, {2324,2323,234,5454,323,232}, {1,2,3222,434,5454,23}));
    return 0;
}
