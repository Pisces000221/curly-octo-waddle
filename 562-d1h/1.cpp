#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
typedef long long int64;

class InducedSubgraphs {
public:

static const int MAXN = 53;
static const int MODULUS = 1e9 + 9;
#define _ % MODULUS
#define __ %= MODULUS
int64 fact[MAXN], fact_inv[MAXN];

inline int64 fpow(int64 base, int exp) {
    int64 ans = 1; for (; exp; exp >>= 1) { if (exp & 1) (ans *= base)__; (base *= base)__; } return ans;
}
inline void preprocess_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) fact[i] = (fact[i - 1] * i)_;
    fact_inv[MAXN - 1] = fpow(fact[MAXN - 1], MODULUS - 2);
    for (int i = MAXN - 2; i >= 0; --i) fact_inv[i] = (fact_inv[i + 1] * (i + 1))_;
}

std::vector<int> e[MAXN];
int dist[MAXN][MAXN];
// [vertex][parent]
// parent=n for global root
int sts[MAXN][MAXN];
int64 f[MAXN][MAXN];

void dfs_hierachy(int u, int p) {
    if (f[u][p] != 0) return;
    sts[u][p] = 1;
    f[u][p] = 1;
    for (int v : e[u]) if (v != p) {
        dfs_hierachy(v, u);
        sts[u][p] += sts[v][u];
        f[u][p] = f[u][p] * f[v][u]_ * fact_inv[sts[v][u]]_;
    }
    (f[u][p] *= fact[sts[u][p] - 1])__;
}

// g[vertex][parent][size 1][size 2]
int g[MAXN][MAXN][MAXN][MAXN];
bool vis_g[MAXN][MAXN];
int64 t[MAXN][MAXN];    // temporary container for g[u][p]
void dfs_g(int u, int p) {
    if (vis_g[u][p]) return;
    vis_g[u][p] = true;
    g[u][p][0][0] = 1;
    int sts_sum = 0;
    for (int v : e[u]) if (v != p) {
        dfs_g(v, u);
        memset(t, 0, sizeof t);
        for (int i = 0; i <= sts[v][u]; ++i)
        for (int j = 0; j <= sts[v][u]; ++j)
            for (int k = 0; k <= sts_sum; ++k)
            for (int l = 0; l <= sts_sum; ++l)
                (t[i + k][j + l] += (int64)g[v][u][i][j] * g[u][p][k][l]_ * fact_inv[i]_ * fact_inv[j]_)__;
        sts_sum += sts[v][u];
        //memcpy(g[u][p], t, sizeof t);
        for (int i = 0; i <= sts_sum; ++i)
            for (int j = 0; j <= sts_sum; ++j) g[u][p][i][j] = t[i][j];
    }
    for (int i = 0; i <= sts[u][p]; ++i)
        for (int j = 0; j <= sts[u][p]; ++j)
            g[u][p][i][j] = (int64)g[u][p][i][j] * fact[i]_ * fact[j]_;
    g[u][p][0][sts[u][p]] = g[u][p][sts[u][p]][0] = f[u][p];
}

int getCount(std::vector<int> edge1, std::vector<int> edge2, int k) {
    if (fact[0] == 0) preprocess_factorials();

    int n = (int)edge1.size() + 1;
    if (k == 1 || k == n) return fact[n];
    for (int i = 0; i < n; ++i) e[i].clear();
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    for (int i = 0; i < n - 1; ++i) {
        e[edge1[i]].push_back(edge2[i]);
        e[edge2[i]].push_back(edge1[i]);
        dist[edge1[i]][edge2[i]] = dist[edge2[i]][edge1[i]] = 1;
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    memset(f, 0, sizeof f);
    for (int i = 0; i < n; ++i) dfs_hierachy(i, n);

    int64 ans = 0;
    if (2 * k <= n) {
        //for (int i = 0; i < n; ++i)
        //    for (int j = 0; j < n; ++j) printf("%lld%c", f[i][j], j == n - 1 ? '\n' : ' ');
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) if (dist[i][j] == n - 2 * k + 1) {
                int u = -1, v = -1;
                for (int w : e[i]) if (dist[w][j] < dist[i][j]) { u = w; break; }
                for (int w : e[j]) if (dist[w][i] < dist[j][i]) { v = w; break; }
                assert(u != -1 && v != -1);
                if (sts[i][u] == k && sts[j][v] == k) (ans += f[i][u] * f[j][v])__;
            }
    } else {    // 2 * k > n
        memset(g, 0, sizeof g);
        memset(vis_g, false, sizeof vis_g);
        for (int i = 0; i < n; ++i) dfs_g(i, n);
        for (int i = 0; i < n; ++i) (ans += g[i][n][n - k][n - k])__;
        (ans *= fact[2 * k - n - 1])__;
    }
    return ans;
}

};

int main()
{
    //printf("%lu\n", sizeof(InducedSubgraphs)); fflush(stdout);
    static InducedSubgraphs worker;
    printf("%d\n", worker.getCount({0, 1}, {1, 2}, 2));
    printf("%d\n", worker.getCount({0, 1, 3}, {2, 2, 2}, 3));
    printf("%d\n", worker.getCount({5, 0, 1, 2, 2}, {0, 1, 2, 4, 3}, 3));
    printf("%d\n", worker.getCount({0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, 11));
    printf("%d\n", worker.getCount({5, 9, 4, 10, 10, 0, 7, 6, 2, 1, 11, 8} , {0, 0, 10, 3, 0, 6, 1, 1, 12, 12, 7, 11}, 6));
    return 0;
}
