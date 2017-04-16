#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

namespace nwf {

static const int MAXN = 52 * 52 + 10;
static const int MAXM = 2e5 + 4;
static const int INF = 0x3fffffff;

int n, m, source, sink;
int head[MAXN], dest[MAXM], cap[MAXM], next[MAXM];

inline void init(int _n) {
    n = _n; m = 0;
    for (int i = 0; i < n; ++i) head[i] = -1;
}
inline void add_edge(int u, int v, int w) {
    dest[m] = v; cap[m] = w; next[m] = head[u]; head[u] = m++;
    dest[m] = u; cap[m] = 0; next[m] = head[v]; head[v] = m++;
}

int d[MAXN];
inline bool level_graph() {
    for (int i = 0; i < n; ++i) d[i] = -1;
    static int q[MAXN], qhead, qtail;
    qhead = 0, qtail = 1; q[0] = source, d[source] = 0;

    while (qhead != qtail) {
        int u = q[qhead++];
        for (int w = head[u]; w != -1; w = next[w])
            if (cap[w] > 0 && d[dest[w]] == -1) {
                d[dest[w]] = d[u] + 1;
                q[qtail++] = dest[w];
            }
    }

    return (d[sink] > 0);
}

int cur[MAXN];
int augment(int u, int cur_cap) {
    if (u == sink) return cur_cap;
    int new_cap;
    for (int &w = cur[u]; w != -1; w = next[w])
        if (cap[w] > 0 && d[dest[w]] == d[u] + 1 && (new_cap = augment(dest[w], std::min(cur_cap, cap[w]))) > 0) {
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

class FoxAndGo3 {
public:

static const int MAXN = 52;
static const int mov[4][2];

int maxEmptyCells(std::vector<std::string> board) {
    int n = board.size();
    nwf::init(n * n + 2);
    nwf::source = n * n, nwf::sink = n * n + 1;
    int ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == 'o') {
                nwf::add_edge(i * n + j, nwf::sink, 1);
                ++ans;
            } else if (board[i][j] == '.') {
                nwf::add_edge(nwf::source, i * n + j, 1);
                for (int k = 0; k < 4; ++k) {
                    int ii = i + mov[k][0], jj = j + mov[k][1];
                    if (ii >= 0 && ii < n && jj >= 0 && jj < n && board[ii][jj] == 'o')
                        nwf::add_edge(i * n + j, ii * n + jj, 1);
                }
                ++ans;
            }
        }
    ans -= nwf::deluge();
    return ans;
}

};
const int FoxAndGo3::mov[4][2] = {{ -1, 0 }, { +1, 0 }, { 0, -1 }, { 0, +1 }};

int main()
{
    FoxAndGo3 worker;
    printf("%d\n", worker.maxEmptyCells({"o.o", ".o.", "o.o"}));
    printf("%d\n", worker.maxEmptyCells({"...", ".o.", "..."}));
    printf("%d\n", worker.maxEmptyCells({"xxxxx", "xxoxx", "xo.ox", "xxoxx", "xxxxx"}));
    printf("%d\n", worker.maxEmptyCells({".xox.", ".o.ox", "x.o.o", "ox.ox", ".ox.."}));
    printf("%d\n", worker.maxEmptyCells({"o.o.o", ".ox..", "oxxxo", "..x..", "o.o.o"}));
    printf("%d\n", worker.maxEmptyCells({"...", "...", "..."}));
    return 0;
}
