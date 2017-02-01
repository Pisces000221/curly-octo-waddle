#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

class EqualSums {
public:

typedef long long int64;
static const int INF = 0x7fffffff;
static const int MAXN = 52;
static const int MODULUS = 1e9 + 7;
#define _ % MODULUS
#define __ %= MODULUS

int n;
bool g[MAXN * 2][MAXN * 2], vis[MAXN * 2];
int pred[MAXN * 2];
std::vector<int> cc[MAXN];

inline void fill_cc(int u) {
    cc[u].push_back(u); vis[u] = true; pred[u] = -1;
    int qtail = 0;
    while (qtail < (int)cc[u].size()) {
        int v = cc[u][qtail++];
        for (int w = 0; w < n * 2; ++w) if (!vis[w] && g[v][w]) {
            cc[u].push_back(w); vis[w] = true; pred[w] = v;
        }
    }
}

int val[MAXN * 2];
// f0: # of solutions with zeroes assigned to some rows
// f:  # of solutions with non-negative integers assigned to all rows (f = f0 * (max-min))
int64 f0[MAXN], f[MAXN];

int count(std::vector<std::string> board) {
    n = (int)board.size();

    memset(g, false, sizeof g);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (board[i][j] != '-') g[i][j + n] = g[j + n][i] = true;
    memset(vis, false, sizeof vis);
    for (int i = 0; i < n; ++i) cc[i].clear();
    for (int i = 0; i < n; ++i) if (!vis[i]) fill_cc(i);

    for (int i = 0; i < n; ++i) if (!cc[i].empty()) {
        //for (int u : cc[i]) printf(" %d", u); putchar('\n');
        // Any element in cc[i] is already independent on later elements in the same CC
        int row_min = +INF, row_max = -INF, col_min = +INF, col_max = -INF;
        for (int u : cc[i]) {
            if (pred[u] == -1) {
                assert(u < n);
                val[u] = 0;
            } else {
                int sum = (u < n ? board[u][pred[u] - n] : board[pred[u]][u - n]) - '0';
                val[u] = sum - val[pred[u]];
            }
            if (u < n) {
                row_min = std::min(row_min, val[u]);
                row_max = std::max(row_max, val[u]);
            } else {
                col_min = std::min(col_min, val[u]);
                col_max = std::max(col_max, val[u]);
            }
            //printf("%d (%d) ← %d\n", u, val[u], pred[u]);
        }
        f0[i] = 1;
        f[i] = (row_min + col_min + 1);
        if (f[i] <= 0) f0[i] = f[i] = 0;
        // Validation
        for (int u : cc[i]) if (u < n) for (int v : cc[i]) if (v >= n) {
            if (board[u][v - n] != '-' && board[u][v - n] != val[u] + val[v] + '0') {
                //printf("Contradiction! %d(%d) + %d(%d) != (%d)\n", u, val[u], v, val[v], board[u][v - n] - '0');
                f0[i] = f[i] = 0; break;
            }
        }
        //printf("Rt=%d  %lld/%lld\n", i, f[i], f0[i]);
    }
    int64 prod_n0 = 1, prod = 1;
    for (int i = 0; i < n; ++i) if (!cc[i].empty()) {
        (prod_n0 *= (f[i] - f0[i]))__;
        (prod *= f[i])__;
    }
    return (prod - prod_n0 + MODULUS)_;
}

#undef _
#undef __
};

int main()
{
    EqualSums worker;
    printf("%d\n", worker.count({"1-", "-2"}));
    printf("%d\n", worker.count({"123", "4--", "--9"}));
    printf("%d\n", worker.count({"9--", "-9-", "--9"}));
    printf("%d\n", worker.count({"--2", "02-", "-10"}));
    return 0;
}
