#include <cstdio>
#include <algorithm>
#include <vector>

class BallsSeparating {
public:

const int INF = 0x7fffffff;

int minOperations(std::vector<int> red, std::vector<int> green, std::vector<int> blue) {
    int n = (int)red.size();
    if (n < 3) return -1;

    int ans = INF, cur;
    for (int r = 0; r < n; ++r)
    for (int g = 0; g < n; ++g) if (g != r)
    for (int b = 0; b < n; ++b) if (b != r && b != g) {
        cur = (green[r] + blue[r]) + (red[g] + blue[g]) + (red[b] + green[b]);
        for (int i = 0; i < n; ++i) if (i != r && i != g && i != b) {
            cur += red[i] + green[i] + blue[i] - std::max(std::max(red[i], green[i]), blue[i]);
        }
        ans = std::min(ans, cur);
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

    printf("%d\n", worker.minOperations({1, 1, 1}, {1, 1, 2}, {1, 1, 3}));
    return 0;
}
