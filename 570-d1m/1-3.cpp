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
// f[subtree root][#selected vertices][#selected CCs][whether root is selected]
int64 f[MAXN][MAXN][MAXN][2];

void dfs_dp(int u, int p) {
    for (int v : e[u]) if (v != p) dfs_dp(v, u);
    static int64 g[MAXN][MAXN];
    f[u][0][0][0] = 1;
    // (1) u is not selected
    for (int v : e[u]) if (v != p) {
        memset(g, 0, sizeof g);
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j) {
                for (int ii = 0; ii <= n - i; ++ii)
                    for (int jj = 0; jj <= n - j; ++jj) {
                        g[ii + i][jj + j] += f[u][ii][jj][0] * (f[v][i][j][0] + f[v][i][j][1]);
                    }
            }
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= i; ++j) f[u][i][j][1] = g[i][j];
    }
    // (2) u is selected
    f[u][1][1][1] = 1;
    for (int v : e[u]) if (v != p) {
        memset(g, 0, sizeof g);
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j) {
                for (int ii = 0; ii <= n - i; ++ii)
                    for (int jj = 1; jj <= n - j; ++jj) {
                        g[ii + i][jj + j] += f[u][ii][jj][1] * f[v][i][j][0];
                        g[ii + i][jj + j - 1] += f[u][ii][jj][1] * f[v][i][j][1];
                    }
            }
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= i; ++j) f[u][i][j][1] = g[i][j];
    }

    //if (u != 2 && u != 3) return;
    printf(">> %d\n", u + 1);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            printf("%lld/%lld%c", f[u][i][j][0], f[u][i][j][1], j == n ? '\n' : ' ');
}

double getvalue(std::vector<int> a, std::vector<int> b) {
    n = (int)a.size() + 1;
    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        e[a[i] - 1].push_back(b[i] - 1);
        e[b[i] - 1].push_back(a[i] - 1);
    }

    memset(f, 0, sizeof f);
    dfs_dp(0, -1);

    int64 tot = 0;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= i; ++j) {
            if (f[0][i][j][0]) printf("%d %d (%d) %lld\n", i, j, max(0, 2 * i - j - 2), f[0][i][j][0]);
            tot += f[0][i][j][0] * max(0, 2 * i - j - 2);
        }
    printf("%lld\n", tot);
    return (double)tot / (1LL << n);
}

};

int main()
{
    CentaurCompany worker;
    // 0.0, 0.125, 0.375, 0.41796875, 0.646484375
    //printf("%.12lf\n", worker.getvalue({1}, {2}));
    //printf("%.12lf\n", worker.getvalue({1,1,1}, {2,3,4}));
    printf("%.12lf\n", worker.getvalue({1,2,3,2,2}, {2,3,4,5,6}));  // Expected 0.375
    //printf("%.12lf\n", worker.getvalue({1,2,3,4,5,6,7,8,9}, {2,3,4,5,6,7,8,9,10}));
    //printf("%.12lf\n", worker.getvalue({10, 7, 2, 5, 6, 2, 4, 9, 7}, {8, 10, 10, 4, 1, 6, 2, 2, 3}));
    return 0;
}
