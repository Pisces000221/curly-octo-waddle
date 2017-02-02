#include <cstdio>
#include <string>
#include <utility>
#include <vector>

class MagicMolecule {
public:

static const int MAXN = 53;
int n;
bool g[MAXN][MAXN];
int w[MAXN];
std::vector<std::pair<int, int>> rm_edges;

int max_removes;
int ans, cur;
bool removed[MAXN]; int rm_ct;
void search(int rm_idx) {
    //printf("[%d %d] %4d: ", rm_edges[rm_idx].first, rm_edges[rm_idx].second, cur);
    //for (int i = 0; i < n; ++i) printf("%d%c", !removed[i], i == n - 1 ? '\n' : ' ');
    if (rm_idx == rm_edges.size()) {
        //printf("%4d: ", cur);
        //for (int i = 0; i < n; ++i) printf("%d%c", !removed[i], i == n - 1 ? '\n' : ' ');
        if (ans < cur) ans = cur;
        return;
    }
    std::pair<int, int> cur_edge = rm_edges[rm_idx];
    if (removed[cur_edge.first] || removed[cur_edge.second]) {
        search(rm_idx + 1);
    } else if (rm_ct < max_removes) {
        ++rm_ct;
        cur -= w[cur_edge.first]; removed[cur_edge.first] = true;
        search(rm_idx + 1);
        cur += w[cur_edge.first]; removed[cur_edge.first] = false;
        cur -= w[cur_edge.second]; removed[cur_edge.second] = true;
        search(rm_idx + 1);
        cur += w[cur_edge.second]; removed[cur_edge.second] = false;
        --rm_ct;
    }
}

int maxMagicPower(std::vector<int> magicPower, std::vector<std::string> magicBond) {
    n = (int)magicPower.size();
    rm_edges.clear();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            g[i][j] = (magicBond[i][j] == 'Y');
            if (!g[i][j] && i < j) rm_edges.push_back({i, j});
        }
    for (int i = 0; i < n; ++i) w[i] = magicPower[i];

    int min_m = (n / 3) * 2 + (n % 3); max_removes = n - min_m;
    ans = -1; cur = 0; rm_ct = 0;
    for (int i = 0; i < n; ++i) cur += magicPower[i];
    for (int i = 0; i < n; ++i) removed[i] = false;
    search(0);
    return ans;
}

};

int main()
{
    MagicMolecule worker;
    printf("%d\n", worker.maxMagicPower({1,2,3}, {"NYY","YNN","YNN"}));
    printf("%d\n", worker.maxMagicPower({1,1,1,1}, {"NNYY","NNYY","YYNN","YYNN"}));
    printf("%d\n", worker.maxMagicPower({86,15,100,93,53,50}, {"NYYYYN","YNNNNY","YNNYYN","YNYNYN","YNYYNY","NYNNYN"}));
    printf("%d\n", worker.maxMagicPower({3969,9430,7242,8549,8190,8368,3704,9740,1691}, {"NYYYYYYYY","YNYYYYYYY","YYNYYYYYY","YYYNYYYYY","YYYYNYYYY","YYYYYNYYY","YYYYYYNNY","YYYYYYNNY","YYYYYYYYN"}));
    return 0;
}
