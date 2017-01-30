#include <cstdio>
#include <cstring>
#include <vector>
typedef long long int64;
template <typename T> inline void upd_max(T &var, const T val) { if (var < val) var = val; }

class MonstersValley {
public:

static const int MAXN = 51;
static const int MAXCOST = 102;

int minimumPrice(std::vector<int64> dread, std::vector<int> price) {
    static int64 f[MAXN][MAXCOST];
    memset(f, 0x80, sizeof f);
    int n = (int)dread.size();

    f[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        // Bribe the monster
        for (int j = 0; j < MAXCOST - price[i]; ++j)
            if (f[i][j] >= 0) upd_max(f[i + 1][j + price[i]], f[i][j] + dread[i]);
        // Do not bribe the monster
        for (int j = 0; j < MAXCOST; ++j)
            if (f[i][j] >= dread[i]) upd_max(f[i + 1][j], f[i][j]);
        //for (int j = 0; j < 10; ++j) printf("%lld%c", f[i + 1][j] < 0 ? -1 : f[i + 1][j], j == 9 ? '\n' : ' ');
    }

    for (int i = 0; i < MAXCOST; ++i) if (f[n][i] > 0) return i;
    return -1;
}

};

int main()
{
    MonstersValley worker;
    printf("%d\n", worker.minimumPrice({8, 5, 10}, {1, 1, 2}));
    printf("%d\n", worker.minimumPrice({1, 2, 4, 1000000000}, {1, 1, 1, 2}));
    printf("%d\n", worker.minimumPrice({200, 107, 105, 206, 307, 400}, {1, 2, 1, 1, 1, 2}));
    printf("%d\n", worker.minimumPrice({5216, 12512, 613, 1256, 66, 17202, 30000, 23512, 2125, 33333}, {2, 2, 1, 1, 1, 1, 2, 1, 2, 1}));
    return 0;
}
