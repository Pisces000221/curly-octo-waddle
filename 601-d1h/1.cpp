#include <cstdio>
#include <cstring>
#include <vector>
typedef long long int64;

class WinterAndShopping {
public:
static const int MAX_SHOPS = 52;
static const int MAX_DAYS = 504;
static const int MAX_BALLS = 103;
static const int MODULUS = 1e9 + 7;
#define _ % MODULUS
#define __ %= MODULUS

int binom[MAX_BALLS * 3][MAX_BALLS * 3] = {{ 0 }};
inline void preprocess() {
    if (binom[0][0] > 0) return;
    binom[0][0] = 1;
    for (int i = 1; i < MAX_BALLS * 3; ++i) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j])_;
    }
}
inline int combination3(int x, int y, int z) {
    return (int64)binom[x + y + z][x] * binom[y + z][y]_;
}

struct shop {
    int r, g, b, len, start, close;
    shop() { }
    shop(int first, int r, int g, int b) :
        r(r), g(g), b(b), len(r + g + b), start(first), close(first + r + g + b) { }
};
std::vector<shop> days[MAX_DAYS];

int f[MAX_DAYS][MAX_BALLS][MAX_BALLS];
int calc(int d, int sr, int sg) {
    // Memorization
    int &ans = f[d][sr][sg];
    if (ans != -1) return ans;

    // Corner cases
    if (d == MAX_DAYS - 1) return (ans = 1);    // Avoid overflow
    if (days[d].empty()) return (ans = calc(d + 1, 0, 0));

    // General cases & invalid cases (should return zero)
    ans = 0;
    shop s = days[d].front();
    int remain_r = s.r - sr, remain_g = s.g - sg,
        remain_b = s.b - (d - s.start - sr - sg);
    if (days[d].size() == 1u) {
        // One store
        if (remain_r + remain_g + remain_b == 1) ans = calc(d + 1, 0, 0);
        else {
            if (remain_r) (ans += calc(d + 1, sr + 1, sg))__;
            if (remain_g) (ans += calc(d + 1, sr, sg + 1))__;
            if (remain_b) (ans += calc(d + 1, sr, sg))__;
        }
    } else {
        // Two stores (s and t)
        // must be the opening day of t since a segment of time will be skipped
        shop t = days[d].back();
        //printf("%d %d %d / %d %d %d\n", s.r, s.g, s.b, t.r, t.g, t.b);
        if (s.close == t.close) {
            // <---- s ---->
            //     <-- t -->
            if (remain_r != t.r || remain_g != t.g || remain_b != t.b) return (ans = 0);
            ans = (int64)combination3(remain_r, remain_g, remain_b) * calc(s.close, 0, 0)_;
        } else if (s.close < t.close) {
            // <---- s ---->
            //     <---- t ---->
            if (remain_r > t.r || remain_g > t.g || remain_b > t.b) return (ans = 0);
            ans = (int64)combination3(remain_r, remain_g, remain_b) * calc(s.close, remain_r, remain_g)_;
        } else {
            // <---- s ---->
            //     <- t ->
            if (remain_r < t.r || remain_g < t.g || remain_b < t.b) return (ans = 0);
            ans = (int64)combination3(t.r, t.g, t.b) * calc(t.close, sr + t.r, sg + t.g)_;
        }
    }

    //printf("%d %d %d: %d\n", d, sr, sg, ans);
    return ans;
}

int getNumber(std::vector<int> first, std::vector<int> red, std::vector<int> green, std::vector<int> blue) {
    for (int i = 0; i < MAX_DAYS; ++i) days[i].clear();
    preprocess();

    int n = (int)first.size();
    for (int i = 0; i < n; ++i) {
        shop s = shop(first[i], red[i], green[i], blue[i]);
        for (int j = s.start; j < s.close; ++j) days[j].push_back(s);
    }
    for (int i = 0; i < MAX_DAYS; ++i) if (days[i].size() >= 2u) {
        if (days[i][0].start > days[i][1].start) std::swap(days[i][0], days[i][1]);
    }

    memset(f, -1, sizeof f);
    return calc(0, 0, 0);
}

};

int main()
{
    static WinterAndShopping worker;
    printf("%d\n", worker.getNumber({1}, {1}, {1}, {1}));   // 6
    printf("%d\n", worker.getNumber({1}, {3}, {0}, {0}));   // 1
    printf("%d\n", worker.getNumber({1, 2}, {1, 1}, {1, 1}, {1, 1}));
    printf("%d\n", worker.getNumber({47, 47}, {1, 0}, {0, 1}, {0, 0}));
    printf("%d\n", worker.getNumber({1, 100, 200}, {100, 1, 0}, {100, 3, 7}, {100, 2, 4}));
    printf("%d\n", worker.getNumber({1, 3}, {3, 4}, {4, 4}, {2, 1}));
    printf("%d\n", worker.getNumber({2, 2, 70, 159}, {100, 20, 21, 52}, {100, 20, 29, 45}, {100, 22, 39, 30}));
    return 0;
}
