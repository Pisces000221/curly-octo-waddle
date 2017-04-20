#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class Mountains {
public:

static const int MAXN = 52;
static const int MAXW = 52;
static const int MODULUS = 1e9 + 9;
#define _  %  MODULUS
#define __ %= MODULUS

int n, w;
int mountain[MAXN];
bool vis[MAXN][MAXW];

std::vector<int> canvas;
std::map<std::pair<int, std::vector<int>>, int> mem;

int search(int idx) {
    if (idx == -1) return 1;
    auto itr = mem.find({ idx, canvas });
    if (itr != mem.end()) return itr->second;

    int ans = 0;
    std::vector<int> canvas_t = canvas;
    for (int pcol = 0; pcol < w; ++pcol) {
        bool valid = true;
        for (int i = 0; i < w; ++i) {
            if ((std::max(0, mountain[idx] - std::abs(pcol - i)) > canvas_t[i]) ^ vis[idx][i]) {
                valid = false; break;
            }
        }
        if (valid) {
            for (int i = 0; i < w; ++i)
                if (vis[idx][i]) canvas[i] = mountain[idx] - std::abs(pcol - i);
            (ans += search(idx - 1))__;
            canvas = canvas_t;
        }
    }

    //printf("[%d] ", idx); for (int h : canvas) printf("%d ", h); printf("| %d\n", ans);
    return (mem[{ idx, canvas }] = ans);
}

int countPlacements(std::vector<int> heights, std::vector<std::string> visibility) {
    n = heights.size();
    w = visibility[0].length();
    for (int i = 0; i < n; ++i) mountain[i] = heights[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < w; ++j) vis[i][j] = (visibility[i][j] == 'X');

    canvas = std::vector<int>(w, 0);
    return search(n - 1);
}

#undef _
#undef __
};

int main()
{
    Mountains worker;
    printf("%d\n", worker.countPlacements({2, 3, 2}, {"------", "XXXX--", "---XXX"}));
    printf("%d\n", worker.countPlacements({4, 3, 4}, {"XXXXX--------", "----------XXX", "----XXXXXXX--"}));
    printf("%d\n", worker.countPlacements({13, 2, 3, 2}, {"XXXXXXXXX", "-XXX-----", "----XXXXX", "-----XXX-"}));
    printf("%d\n", worker.countPlacements({8, 2, 9, 3, 10}, {"X------", "-------", "------X", "-------", "XXXXXXX"}));
    printf("%d\n", worker.countPlacements({20, 20, 20, 20, 20, 20, 45, 50, 49, 50}, {"-------------------", "-------------------", "-------------------", "-------------------", "-------------------", "-------------------", "-------------------", "------------XXXXXXX", "XXXXXXX------------", "XXXXXXXXXXXXXXXXXXX"}));
    return 0;
}
