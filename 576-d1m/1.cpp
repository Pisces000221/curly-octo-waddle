#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

class TheExperiment {
public:

typedef long long int64;
static const int MAXN = 303;
static const int MAXM = 302;
static const int MODULUS = 1e9 + 9;
#define _  %  MODULUS
#define __ %= MODULUS

int N;
int a[MAXN], sum[MAXN];
int64 f[MAXN][MAXM], g[MAXN][MAXM], h[MAXN][MAXM];

int countPlacements(std::vector<std::string> intensity, int M, int L, int A, int B) {
    N = 0;
    sum[0] = 0;
    for (auto s : intensity)
        for (int i = 0; i < s.length(); ++i) {
            a[++N] = s[i] - '0';
            sum[N] = sum[N - 1] + a[N];
        }

    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    memset(h, 0, sizeof h);
    h[0][0] = 1;

    for (int i = 1; i <= N; ++i)
        for (int j = 0; j <= M; ++j) {
            if (j > 0) {
                for (int k = std::max(0, i - L); k < i; ++k)
                    if (sum[i] - sum[k] >= A && sum[i] - sum[k] <= B) {
                        //printf("  %d %d <- %d %d\n", i, j, k, j - 1);
                        if (k != i - L) f[i][j] += (f[k][j - 1] + h[k][j - 1]);
                        g[i][j] += g[k][j - 1];
                    }
                if (i >= L && sum[i] - sum[i - L] >= A && sum[i] - sum[i - L] <= B)
                    g[i][j] += (f[i - L][j - 1] + h[i - L][j - 1]);
            }
            f[i][j]__;
            g[i][j]__;
            h[i][j] = (h[i - 1][j] + g[i - 1][j])_;
            //if (f[i][j]) printf("f %d %d: %lld\n", i, j, f[i][j]);
            //if (g[i][j]) printf("g %d %d: %lld\n", i, j, g[i][j]);
            //if (h[i][j]) printf("h %d %d: %lld\n", i, j, h[i][j]);
        }

    return (int)((g[N][M] + h[N][M])_);
}

};

int main()
{
    TheExperiment worker;
    printf("%d\n", worker.countPlacements({"341156"}, 3, 3, 6, 10));
    printf("%d\n", worker.countPlacements({"999112999"}, 2, 4, 21, 30));
    printf("%d\n", worker.countPlacements({"111"}, 2, 2, 2, 3));
    printf("%d\n", worker.countPlacements({"59059", "110", "1132230231"}, 1, 5, 10, 20));
    printf("%d\n", worker.countPlacements({"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"}, 12, 8, 4, 2700));
    return 0;
}
