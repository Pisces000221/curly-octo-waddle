#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

class TreeUnion {
public:

static const int MAXN = 302;

inline std::vector<int> parseList(const std::vector<std::string> &ls) {
    std::vector<int> ret;
    int cur = 0;
    for (auto s : ls) {
        for (int i = 0; i < s.length(); ++i)
            if (s[i] == ' ') ret.push_back(cur), cur = 0;
            else cur = cur * 10 + s[i] - '0';
    }
    ret.push_back(cur);
    return ret;
}

int n;
std::vector<int> e[MAXN];

int ans[4];
void dfs(int u, int p, int d) {
    if (d >= 1 && d <= 4) ++ans[d - 1];
    if (d == 4) return;
    for (int v : e[u]) if (v != p) dfs(v, u, d + 1);
}
inline std::vector<int> countOnATree(const std::vector<int> &p) {
    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        e[i + 1].push_back(p[i]);
        e[p[i]].push_back(i + 1);
    }
    std::fill(ans, ans + 4, 0);
    for (int i = 0; i < n; ++i) dfs(i, -1, 0);
    return { ans[0] / 2, ans[1] / 2, ans[2] / 2, ans[3] / 2 };
}

double expectedCycles(std::vector<std::string> _tree1, std::vector<std::string> _tree2, int K) {
    auto t1 = parseList(_tree1), t2 = parseList(_tree2);
    this->n = t1.size() + 1;
    auto t1_pairs = countOnATree(t1), t2_pairs = countOnATree(t2);
    //printf("%d %d %d %d\n", t1_pairs[0], t1_pairs[1], t1_pairs[2], t1_pairs[3]);

    double ans = 0.0;
    for (int i = 1; i <= 4; ++i) {
        int j = K - i - 2;
        if (j < 0) break;
        ans += (double)t1_pairs[i - 1] * t2_pairs[j - 1] * 2 / (n * (n - 1));
    }
    return ans;
}

};

int main()
{
    TreeUnion worker;
    printf("%.4lf\n", worker.expectedCycles({"0"}, {"0"}, 4));
    printf("%.4lf\n", worker.expectedCycles({"0 1"}, {"0 1"}, 4));
    printf("%.4lf\n", worker.expectedCycles({"0 1"}, {"0 1"}, 6));
    printf("%.4lf\n", worker.expectedCycles({"0 ", "1 1 1"}, {"0 1 0 ", "1"}, 5));
    printf("%.4lf\n", worker.expectedCycles({"0 1 2 0 1 2 0 1 2 5 6 1", "0 11", " 4"}, {"0 1 1 0 2 3 4 3 4 6 6", " 10 12 12"}, 7));
    return 0;
}
