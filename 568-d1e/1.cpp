#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

class BallsSeparating {
public:

const int INF = 0x7fffffff;

int minOperations(std::vector<int> red, std::vector<int> green, std::vector<int> blue) {
    int n = (int)red.size();
    int sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int val : red) sum_red += val;
    for (int val : green) sum_green += val;
    for (int val : blue) sum_blue += val;
    if (n < !!sum_red + !!sum_green + !!sum_blue) return -1;

    int ans = 0;
    bool slctd[n]; std::fill(slctd, slctd + n, false);

    std::pair<int, int> best;
    if (sum_red != 0) {
        best = std::make_pair(INF, -1);
        for (int i = 0; i < n; ++i) if (!slctd[i]) best = std::min(best, {green[i] + blue[i], i});
        ans += best.first; slctd[best.second] = true;
    }
    if (sum_blue != 0) {
        best = std::make_pair(INF, -1);
        for (int i = 0; i < n; ++i) if (!slctd[i]) best = std::min(best, {red[i] + green[i], i});
        ans += best.first; slctd[best.second] = true;
    }
    if (sum_green != 0) {
        best = std::make_pair(INF, -1);
        for (int i = 0; i < n; ++i) if (!slctd[i]) best = std::min(best, {red[i] + blue[i], i});
        ans += best.first; slctd[best.second] = true;
    }

    for (int i = 0; i < n; ++i) if (!slctd[i]) {
        ans += red[i] + green[i] + blue[i] - std::max(std::max(red[i], green[i]), blue[i]);
    }
    return ans;
}

};

int main()
{
    BallsSeparating worker;
    printf("%d\n", worker.minOperations({1, 1, 1}, {1, 1, 1}, {1, 1, 1}));
    printf("%d\n", worker.minOperations({5}, {6}, {8}));
    printf("%d\n", worker.minOperations({4, 6, 5, 7}, {7, 4, 6, 3}, {6, 5, 3, 8}));
    printf("%d\n", worker.minOperations({7, 12, 9, 9, 7}, {7, 10, 8, 8, 9}, {8, 9, 5, 6, 13}));

    printf("%d\n", worker.minOperations({4, 0}, {0, 3}, {0, 0}));
    printf("%d\n", worker.minOperations({4, 0}, {1, 3}, {0, 0}));
    printf("%d\n", worker.minOperations({0}, {3}, {0}));
    printf("%d\n", worker.minOperations({0, 0}, {3, 0}, {2, 0}));
    printf("%d\n", worker.minOperations({0}, {0}, {0}));
    return 0;
}
