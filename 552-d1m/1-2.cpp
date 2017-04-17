#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

class FoxAndFlowerShopDivOne {
public:

static const int MAXN = 32;
static const int INF = 0x3fffffff;

int n, m, maxDiff;
int s[MAXN][MAXN];
int sum[MAXN][MAXN], cnt[MAXN][MAXN];
inline int val(const char ch) {
    switch (ch) { case 'L': return +1; case 'P': return -1; case '.': default: return 0; }
}
int subrectAns[2][MAXN * MAXN * 2];
inline void processSubrect(int ptr, int col_s, int col_f) {
    std::fill(&subrectAns[ptr][0], &subrectAns[ptr][0] + MAXN * MAXN * 2, -INF);
    for (int r1 = 0; r1 < n; ++r1)
        for (int c1 = col_s; c1 < col_f; ++c1)
            for (int r2 = r1; r2 < n; ++r2)
                for (int c2 = c1; c2 < col_f; ++c2) {
                    int diff = sum[r2 + 1][c2 + 1] - sum[r2 + 1][c1] - sum[r1][c2 + 1] + sum[r1][c1];
                    subrectAns[ptr][diff + MAXN * MAXN] = std::max(subrectAns[ptr][diff + MAXN * MAXN], cnt[r2 + 1][c2 + 1] - cnt[r2 + 1][c1] - cnt[r1][c2 + 1] + cnt[r1][c1]);
                }
}
inline int calculate() {
    std::fill(&sum[0][0], &sum[0][0] + MAXN * MAXN, 0);
    std::fill(&cnt[0][0], &cnt[0][0] + MAXN * MAXN, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + s[i][j];
            cnt[i + 1][j + 1] = cnt[i][j + 1] + cnt[i + 1][j] - cnt[i][j] + std::abs(s[i][j]);
        }

    int ans = -INF;
    for (int barrier = 1; barrier < m; ++barrier) {
        processSubrect(0, 0, barrier);
        processSubrect(1, barrier, m);
        for (int i = -MAXN * MAXN; i < MAXN * MAXN; ++i)
            for (int j = -MAXN * MAXN; j < MAXN * MAXN; ++j)
                if (std::abs(i + j) <= maxDiff)
                    ans = std::max(ans, subrectAns[0][i + MAXN * MAXN] + subrectAns[1][j + MAXN * MAXN]);
    }
    return ans;
}

int theMaxFlowers(std::vector<std::string> flowers, int maxDiff) {
    int ans = -INF;
    this->maxDiff = maxDiff;
    n = flowers.size(), m = flowers[0].length();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) s[i][j] = val(flowers[i][j]);
    ans = std::max(ans, calculate());
    std::swap(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) s[i][j] = val(flowers[j][i]);
    ans = std::max(ans, calculate());
    return (ans < 0 ? -1 : ans);
}

};

int main()
{
    FoxAndFlowerShopDivOne worker;
    printf("%d\n", worker.theMaxFlowers({"LLL", "PPP", "LLL"}, 1));
    printf("%d\n", worker.theMaxFlowers({"LLL", "PPP", "LLL"}, 0));
    printf("%d\n", worker.theMaxFlowers({"...", "...", "..."}, 3));
    printf("%d\n", worker.theMaxFlowers({"LLPL.LPP", "PLPPPPLL", "L.P.PLLL", "LPL.PP.L", ".LLL.P.L", "PPLP..PL"}, 2));
    printf("%d\n", worker.theMaxFlowers({"LLLLLLLLLL", "LLLLLLLLLL", "LLLLLLLLLL", "LLLLLLLLLL", "LLLLLLLLLL"}, 0));
    printf("%d\n", worker.theMaxFlowers({"LLLP..LLP.PLL.LL..LP", "L.PL.L.LLLL.LPLLPLP.", "PLL.LL.LLL..PL...L..", ".LPPP.PPPLLLLPLP..PP", "LP.P.PPL.L...P.L.LLL", "L..LPLPP.PP...PPPL..", "PP.PLLL.LL...LP..LP.", "PL...P.PPPL..PLP.L..", "P.PPPLPLP.LL.L.LLLPL", "PLLPLLP.LLL.P..P.LPL", "..LLLPLPPPLP.P.LP.LL", "..LP..L..LLPPP.LL.LP", "LPLL.PLLPPLP...LL..P", "LL.....PLL.PLL.P....", "LLL...LPPPPL.PL...PP", ".PLPLLLLP.LPP...L...", "LL...L.LL.LLLPLPPPP.", "PLPLLLL..LP.LLPLLLL.", "PP.PLL..L..LLLPPL..P", ".LLPL.P.PP.P.L.PLPLL"}, 9));

    printf("%d\n", worker.theMaxFlowers({"LLLLLL", "PPLPPP"}, 1));
    printf("%d\n", worker.theMaxFlowers({"LLLPLPLLLPPPPLPLPLLP", "LPPLPLPLPLPLPLPLLLPP"}, 2));
    printf("%d\n", worker.theMaxFlowers({"L", "L", "L", "P", "L"}, 1));
    return 0;
}
