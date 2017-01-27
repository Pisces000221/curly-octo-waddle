#include <cstdio>
#include <algorithm>
#include <vector>

class KingdomAndTrees {
public:

inline bool check(const std::vector<int> &heights, int max_change) {
    int n = (int)heights.size();
    int last = 0;
    for (int i = 0; i < n; ++i) {
        if (heights[i] > last) {
            last = std::max(last + 1, heights[i] - max_change);
        } else {
            if (heights[i] + max_change >= last + 1) {
                last = last + 1;
            } else return false;
        }
    }
    return true;
}

int minLevel(std::vector<int> heights) {
    int n = (int)heights.size();
    int lo = -1, hi = *std::max_element(heights.begin(), heights.end()) + n + 1, mid;
    while (lo < hi - 1) {
        mid = (lo + hi) >> 1;
        if (check(heights, mid)) hi = mid; else lo = mid;
    }
    return hi;
}

};

int main()
{
    KingdomAndTrees worker;
    printf("%d\n", worker.minLevel({9, 5, 11}));
    printf("%d\n", worker.minLevel({5, 8}));
    printf("%d\n", worker.minLevel({1, 1, 1, 1, 1 }));
    printf("%d\n", worker.minLevel({548, 47, 58, 250, 2012}));
    return 0;
}
