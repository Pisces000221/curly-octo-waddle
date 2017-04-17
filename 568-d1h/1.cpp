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

inline bool intersects(const determined a, const determined b) {
    return (std::get<0>(a) < std::get<0>(b)) ^ (std::get<1>(a) < std::get<1>(b)) ^ 1;
}

bool check(int seq_len, std::vector<determined> list) {
    dud.init((seq_len + 1) * 2);
    std::vector<determined> bucket[2];
    for (auto &pair : list) bucket[std::get<2>(pair)].push_back(pair);
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j < bucket[i].size(); ++j)
            for (int k = j + 1; k < bucket[i].size(); ++k)
                if (intersects(bucket[i][j], bucket[i][k])) return false;
    }
    puts("===");
    for (auto &pair : list) {
        int p = std::get<0>(pair), q = std::get<1>(pair);
        bool det_parity = std::get<2>(pair);
        bool gap_parity = (det_parity ? 0 : ((q - p + 1) & 1));
        printf("%d %d %d %d\n", p, q, det_parity, gap_parity);
        // Gap
        dud.unite(p * 2, ((q + 1) * 2) ^ gap_parity);
        dud.unite(p * 2 + 1, ((q + 1) * 2 + 1) ^ gap_parity);
        // Endpoints
        dud.unite(p * 2, ((p + 1) * 2) ^ det_parity);
        dud.unite(p * 2 + 1, ((p + 1) * 2 + 1) ^ det_parity);
        dud.unite(q * 2, ((q + 1) * 2) ^ det_parity);
        dud.unite(q * 2 + 1, ((q + 1) * 2 + 1) ^ det_parity);
    }
    for (int i = 0; i <= seq_len; ++i)
        if (dud.root(i * 2) == dud.root(i * 2 + 1)) return false;
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

    for (int i = 0; i < (1 << mapped_ct); ++i) {
        std::vector<determined> list;
        for (int j = 0; j < mapped_ct; ++j)
            list.push_back({ occ[mapped[j]][0], occ[mapped[j]][1], (i >> j) & 1 });
        // occ[*][0] < occ[*][1]; or both equals -1
        if (check(n * 2, list)) return "POSSIBLE";
    }
    return "IMPOSSIBLE";
}

};

int main()
{
    DisjointSemicircles worker;
    //puts(worker.getPossibility({ -1, 0, -1, -1, 0, -1 }).c_str());
    puts(worker.getPossibility({ 1, -1, 2, 1, -1, 2 }).c_str());
    /*puts(worker.getPossibility({ 2, -1, -1, 0, -1, -1, 2, 0 }).c_str());
    puts(worker.getPossibility({ -1, 1, 3, -1, 1, 3, -1, -1 }).c_str());
    puts(worker.getPossibility({ -1, 5, -1, -1, 3, 6, 8, -1, 10, 7, -1, 7, 8, 0, 11, -1, -1, 11, 0, 10, 4, -1, 6, 5, -1, -1, 9, 9, 4, 3 }).c_str());
    puts(worker.getPossibility({ 4, -1, 2, 4, -1, 3, 3, 12, 2, 5, -1, 0, 9, 9, 8, -1, 12, 8, -1, 6, 0, -1, -1, -1, 5, 6, 10, -1, -1, 10 }).c_str());
    puts(worker.getPossibility({ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }).c_str());*/
    return 0;
}
