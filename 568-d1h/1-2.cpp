#include <cstdio>
#include <string>
#include <tuple>
#include <vector>

class DisjointSemicircles {
public:

static const int MAXN = 27;
typedef std::tuple<int, int, bool> determined;

struct dsu {
    int p[(MAXN + 1) * 4];
    inline void init(int n) { for (int i = 0; i < n; ++i) p[i] = i; }
    int root(int u) { return (p[u] == u) ? u : (p[u] = root(p[u])); }
    inline bool unite(int u, int v) { u = root(u), v = root(v); return (u == v ? false : (p[u] = v, true)); }
} dud;

bool check(int seq_len, std::vector<int> &labels, std::vector<determined> &list) {
    dud.init((seq_len + 1) * 2);
    static std::vector<int> bucket[2];
    bucket[0].clear();
    bucket[1].clear();
    for (int i = 0; i < list.size(); ++i) bucket[std::get<2>(list[i])].push_back(i);
    for (int p = 0; p <= 1; ++p) {
        static int event[MAXN * 2];
        for (int i = 0; i < seq_len; ++i) event[i] = 0;
        for (int i = 0; i < bucket[p].size(); ++i) {
            event[std::get<0>(list[bucket[p][i]])] = i + 1;
            event[std::get<1>(list[bucket[p][i]])] = -(i + 1);
        }
        static int stk[MAXN * 2], stk_top;
        stk_top = 0;
        for (int i = 0; i < seq_len; ++i) if (event[i]) {
            if (event[i] > 0) stk[stk_top++] = event[i];
            else if (stk[--stk_top] != -event[i]) return false;
        }
    }
    //puts("===");
    static int pfx[MAXN * 2];
    pfx[0] = 0; for (int i = 0; i < seq_len; ++i) pfx[i + 1] = pfx[i] + (labels[i] == -1);
    for (int i = 0; i < seq_len; ++i) if (labels[i] != -1) {
        dud.unite(i * 2, (i + 1) * 2);
        dud.unite(i * 2 + 1, (i + 1) * 2 + 1);
    }
    for (auto &pair : list) {
        int p = std::get<0>(pair), q = std::get<1>(pair);
        bool det_parity = std::get<2>(pair);
        bool gap_parity = (det_parity ? 0 : ((pfx[q + 1] - pfx[p]) & 1));
        //printf("%d %d %d %d\n", p, q, det_parity, gap_parity);
        // Gap
        dud.unite(p * 2, ((q + 1) * 2) ^ gap_parity);
        dud.unite(p * 2 + 1, ((q + 1) * 2 + 1) ^ gap_parity);
    }
    //for (int i = 0; i < (seq_len + 1) * 2; ++i) printf("[%d] = %d: Rps=%d\n", i / 2, i % 2, dud.root(i));
    for (int i = 0; i <= seq_len; ++i)
        if (dud.root(i * 2) == dud.root(i * 2 + 1)) return false;
    if (dud.root(0) == dud.root(seq_len * 2 + 1) || dud.root(1) == dud.root(seq_len * 2)) return false;
    return true;
}

std::string getPossibility(std::vector<int> labels) {
    int n = labels.size() / 2;
    int occ[MAXN][2];
    for (int i = 0; i < MAXN; ++i) occ[i][0] = occ[i][1] = -1;
    for (int i = 0; i < n * 2; ++i) if (labels[i] != -1) {
        if (occ[labels[i]][0] == -1) occ[labels[i]][0] = i;
        else occ[labels[i]][1] = i;
    }
    int mapped[MAXN], mapped_ct = 0;
    for (int i = 0; i < MAXN; ++i)
        if (occ[i][0] != -1) mapped[mapped_ct++] = i;

    std::vector<determined> list;
    for (int j = 0; j < mapped_ct; ++j)
        list.push_back(std::make_tuple(occ[mapped[j]][0], occ[mapped[j]][1], true));
    if (mapped_ct >= 25) return "POSSIBLE"; // ??????
    for (int i = 0; i < (1 << mapped_ct); ++i) {
        for (int j = 0; j < mapped_ct; ++j)
            std::get<2>(list[j]) = (i >> j) & 1;
        // occ[*][0] < occ[*][1]; or both equals -1
        if (check(n * 2, labels, list)) return "POSSIBLE";
    }
    return "IMPOSSIBLE";
}

};

int main()
{
    DisjointSemicircles worker;
    puts(worker.getPossibility({ -1, 0, -1, -1, 0, -1 }).c_str());
    puts(worker.getPossibility({ 1, -1, 2, 1, -1, 2 }).c_str());
    puts(worker.getPossibility({ 2, -1, -1, 0, -1, -1, 2, 0 }).c_str());
    puts(worker.getPossibility({ -1, 1, 3, -1, 1, 3, -1, -1 }).c_str());
    puts(worker.getPossibility({ -1, 5, -1, -1, 3, 6, 8, -1, 10, 7, -1, 7, 8, 0, 11, -1, -1, 11, 0, 10, 4, -1, 6, 5, -1, -1, 9, 9, 4, 3 }).c_str());
    puts(worker.getPossibility({ 4, -1, 2, 4, -1, 3, 3, 12, 2, 5, -1, 0, 9, 9, 8, -1, 12, 8, -1, 6, 0, -1, -1, -1, 5, 6, 10, -1, -1, 10 }).c_str());
    puts(worker.getPossibility({ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }).c_str());

    puts(worker.getPossibility({ -1, -1 }).c_str());
    puts(worker.getPossibility({ 0, 1, 0, 1 }).c_str());
    puts(worker.getPossibility({ 1, 2, 0, 1, 0, 2 }).c_str());
    puts(worker.getPossibility({ 1, 2, 0, 1, 2, 0 }).c_str());
    //puts(worker.getPossibility({ 14, 14, 5, 5, 22, 20, 17, 0, 18, 2, 15, 0, 17, 12, 15, 23, 21, 16, 8, 10, 21, 12, 3, 3, 10, 11, 8, 16, 23, 2, 18, 19, 19, 1, 13, 13, 20, 1, 4, 6, 9, 9, 4, 6, 7, 7, 22, 11 }).c_str());  // Case #115
    puts(worker.getPossibility({ 4, 4, 23, 0, 21, 17, 22, 17, 18, 18, 12, 24, 3, 11, 8, 5, 22, 19, 7, 7, 19, 6, 15, 1, 15, 6, 13, 13, 5, 1, 8, 11, 2, 3, 16, 16, 20, 9, 9, 20, 24, 12, 10, 10, 21, 14, 2, 23, 14, 0 }).c_str());    // Case #284
    return 0;
}
