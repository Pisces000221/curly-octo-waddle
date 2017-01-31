#include <cstdio>
#include <set>
#include <string>
#include <vector>

class CirclesGame {
public:

static const int MAXN = 52;

static inline bool circle_contains(int x1, int y1, int r1, int x2, int y2, int r2) {
    int dist_sq = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    return r1 > r2 && dist_sq < (r1 - r2) * (r1 - r2);
}

int p[MAXN], max_r[MAXN];
std::vector<int> e[MAXN];

int grundy[MAXN];
void iterate_path(int u, std::set<int> &s, int xor_sum) {
    for (int v : e[u]) xor_sum ^= grundy[v];
    s.insert(xor_sum);
    for (int v : e[u]) iterate_path(v, s, xor_sum ^ grundy[v]);
}
void calc_grundy(int u) {
    for (int v : e[u]) calc_grundy(v);
    std::set<int> s;
    iterate_path(u, s, 0);
    int mex = 0;
    for (int val : s) if (val == mex) ++mex; else break;
    grundy[u] = mex;
}

std::string whoCanWin(std::vector<int> x, std::vector<int> y, std::vector<int> r) {
    int n = (int)x.size();
    for (int i = 0; i < n; ++i) p[i] = -1;
    for (int i = 0; i < n; ++i) {
        max_r[i] = 1e7;
        for (int j = 0; j < n; ++j) if (max_r[i] > r[j] && circle_contains(x[j], y[j], r[j], x[i], y[i], r[i])) {
            max_r[i] = r[j];
            p[i] = j;
        }
    }
    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < n; ++i) if (p[i] != -1) e[p[i]].push_back(i);

    int overall_grundy = 0;
    for (int i = 0; i < n; ++i) if (p[i] == -1) {
        calc_grundy(i);
        overall_grundy ^= grundy[i];
    }
    return (overall_grundy == 0 ? "Bob" : "Alice");
}

};

int main()
{
    CirclesGame worker;
    puts(worker.whoCanWin({0}, {0}, {1}).c_str());
    puts(worker.whoCanWin({0, 3}, {0, 0}, {1, 1}).c_str());
    puts(worker.whoCanWin({0, 0, 5}, {0, 0, 0}, {1, 2, 1}).c_str());
    puts(worker.whoCanWin({10,20,30,40,50,60,70,80}, {8,7,6,5,4,3,2,1}, {2,2,2,2,2,2,2,2}).c_str());
    return 0;
}
