#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

class BoardPainting {
public:

static const int MAXN = 51;
static const int MAXV = MAXN * MAXN + 5;
static const int MAXE = MAXN * MAXN * 24;
static const int INF = 0x3fffffff;

int n, e, source, sink;
int head[MAXV], dest[MAXE], cap[MAXE], next[MAXE];
int cur[MAXV];
inline void add_edge(int u, int v, int c, int c_r = 0) {
    //printf("%d %d %d\n", u, v, c);
    dest[e] = v; cap[e] = c; next[e] = head[u]; head[u] = e++;
    dest[e] = u; cap[e] = c_r; next[e] = head[v]; head[v] = e++;
}

int d[MAXV];
inline bool level() {
    memset(d, -1, sizeof d);
    static int q[MAXV], qhead, qtail;
    d[source] = 0, qhead = 1, qtail = 0, q[0] = source;
    while (qhead > qtail) {
        int u = q[qtail++];
        for (int w = head[u]; w != -1; w = next[w]) if (cap[w] > 0 && d[dest[w]] == -1) {
            d[dest[w]] = d[u] + 1;
            q[qhead++] = dest[w];
        }
    }
    return (d[sink] > 0);
}
inline int augment(int u, int cur_cap = INF) {
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
inline int flow() {
    int ans = 0, aug;
    while (level()) {
        for (int i = 0; i < n; ++i) cur[i] = head[i];
        while ((aug = augment(source)) > 0) ans += aug;
    }
    return ans;
}
inline void flow_init(int vertices) {
    n = vertices; e = 0; source = n - 2; sink = n - 1;
    for (int i = 0; i < n; ++i) head[i] = -1;
}

int minimalSteps(std::vector<std::string> target) {
    static const int mov[4][2] = {{+1, 0}, {-1, 0}, {0, +1}, {0, -1}};
    int rows = (int)target.size(), cols = (int)target[0].length();
    flow_init(rows * cols + 2);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) if (target[i][j] == '#') {
            static bool neighbour[4];
            for (int dir = 0; dir < 4; ++dir) {
                int nw_i = i + mov[dir][0], nw_j = j + mov[dir][1];
                if (nw_i >= 0 && nw_i < rows && nw_j >= 0 && nw_j < cols && target[nw_i][nw_j] == '#') {
                    if (target[i][j] == '#' && dir % 2 == 0) add_edge(i * cols + j, nw_i * cols + nw_j, 1, 1);
                    neighbour[dir] = true;
                } else neighbour[dir] = false;
            }
            if ((int)neighbour[0] + neighbour[1] < 2)
                add_edge(source, i * cols + j, 2 - neighbour[0] - neighbour[1]);
            if ((int)neighbour[2] + neighbour[3] < 2)
                add_edge(i * cols + j, sink, 2 - neighbour[2] - neighbour[3]);
        }
    return flow() / 2;
}

};

int main()
{
    BoardPainting worker;
    printf("%d\n", worker.minimalSteps({"#####"}));
    printf("%d\n", worker.minimalSteps({"#####", ".....", "#####", ".....", "#####"}));
    printf("%d\n", worker.minimalSteps({"..#..", "..#..", "#####", "..#..", "..#.."}));
    printf("%d\n", worker.minimalSteps({"#####", "..#..", "#####", "..#..", "#####"}));
    printf("%d\n", worker.minimalSteps({"#.", ".#"}));
    return 0;
}
