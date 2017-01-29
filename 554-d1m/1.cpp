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
    ans.push_back(p[0].second);
    for (int i = 1; i < n; ++i) {
        if (p[i].second < ans.front()) ans.insert(ans.begin(), p[i].second);
        else ans.push_back(p[i].second);
    }
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
    print_vector(worker.find({8, 8, 1}));   // Fail!
    return 0;
}
