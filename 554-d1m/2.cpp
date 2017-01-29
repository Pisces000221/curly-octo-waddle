#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

class TheBrickTowerMediumDivOne {
public:

static const int MAXN = 50;

std::vector<int> find(std::vector<int> heights) {
    int n = (int)heights.size();
    static std::pair<int, int> p[MAXN];
    for (int i = 0; i < n; ++i) p[i] = std::make_pair(heights[i], i);
    std::sort(p, p + n);
    std::vector<int> ans;
    ans.push_back(n + 114514);
    for (int i = 0, j, k; i < n; ) {
        j = i; while (j < n && p[j].first == p[i].first) ++j;
        for (k = i; k < j && p[k].second < ans.front(); ++k) ;
        for (int l = k - 1; l >= i; --l) ans.insert(ans.begin(), p[l].second);
        for (i = k; i < j; ++i) ans.push_back(p[i].second);
    }
    for (auto it = ans.begin(); it != ans.end(); ++it)
        if (*it == n + 114514) { ans.erase(it); break; }
    return ans;
}

};

inline void print_vector(const std::vector<int> &v) {
    for (int x : v) printf(" %d", x); putchar('\n');
}
int main()
{
    TheBrickTowerMediumDivOne worker;
    print_vector(worker.find({4, 7, 5}));
    print_vector(worker.find({4, 4, 4, 4, 4, 4, 4}));
    print_vector(worker.find({2, 3, 3, 2}));
    print_vector(worker.find({13, 32, 38, 25, 43, 47, 6}));
    print_vector(worker.find({3, 1, 1, 4, 1, 1, 3, 4}));
    print_vector(worker.find({8, 8, 1}));
    return 0;
}
