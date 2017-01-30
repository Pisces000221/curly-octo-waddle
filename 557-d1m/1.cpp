#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

class Incubator {
public:

static const int MAXN = 52;
int n;
bool g[MAXN][MAXN], vis[MAXN]; int match[MAXN];

bool dfs(int u) {
    for (int v = 0; v < n; ++v) if (!vis[v] && g[u][v]) {
        vis[v] = true;
        if (match[v] == -1 || dfs(match[v])) { match[v] = u; return true; }
    }
    return false;
}
inline int bipartite_match() {
    int ans = 0;
    memset(match, -1, sizeof match);
    for (int i = 0; i < n; ++i) {
        memset(vis, false, sizeof vis);
        if (dfs(i)) ++ans;
    }
    return ans;
}

int maxMagicalGirls(std::vector<std::string> love) {
    this->n = (int)love.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) g[i][j] = (love[i][j] == 'Y');
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) g[i][j] |= (g[i][k] && g[k][j]);
    return n - bipartite_match();
}

};

int main()
{
    Incubator worker;
    printf("%d\n", worker.maxMagicalGirls({"NY","NN"}));
    printf("%d\n", worker.maxMagicalGirls({"NYN", "NNY", "NNN"}));
    printf("%d\n", worker.maxMagicalGirls({"NNYNN","NNYNN","NNNYY","NNNNN","NNNNN"}));
    printf("%d\n", worker.maxMagicalGirls({"NNNNN","NYNNN","NYNYN","YNYNN","NNNNN"}));
    printf("%d\n", worker.maxMagicalGirls({"NNNNN","NNNNN","NNNNN","NNNNN","NNNNN"}));
    printf("%d\n", worker.maxMagicalGirls({"NNYNNNNN","NNNYNNNN","NNNNYNNN","NNYNNNNN","NNNNNYYN","NNNYNNNY","NNNNNNNN","NNNNNNNN"}));
    printf("%d\n", worker.maxMagicalGirls({"Y"}));
    return 0;
}
