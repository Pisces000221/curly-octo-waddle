#include <cstdio>
#include <vector>

class DrawingPointsDivOne {
public:

static const int MAXN = 52;
static const int MAXCOORD = 148;
static const int COORD_OFFSET = MAXCOORD / 2;

inline bool check_steps(const std::vector<int> &x, const std::vector<int> &y, int k) {
    int n = (int)x.size();
    static bool f[MAXCOORD * 2][MAXCOORD * 2], g[MAXCOORD * 2][MAXCOORD * 2];
    for (int i = 0; i < MAXCOORD * 2; ++i)
        for (int j = 0; j < MAXCOORD * 2; ++j) {
            f[i][j] = g[i][j] = false;
            for (int p = 0; p < n; ++p)
                if (x[p] >= i - k && x[p] <= i && y[p] >= j - k && y[p] <= j) {
                    g[i][j] = true;
                    if (x[p] == i && y[p] == j) { f[i][j] = true; break; }
                }
        }
    static int sum[MAXCOORD * 2][MAXCOORD * 2];
    sum[0][0] = g[0][0];
    for (int i = 1; i < MAXCOORD * 2; ++i) {
        sum[0][i] = sum[0][i - 1] + g[0][i];
        sum[i][0] = sum[i - 1][0] + g[i][0];
    }
    for (int i = 1; i < MAXCOORD * 2; ++i)
        for (int j = 1; j < MAXCOORD * 2; ++j)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + g[i][j];
    // Check for (k+1) * (k+1) squares
    for (int i = k; i < MAXCOORD * 2; ++i)
        for (int j = k; j < MAXCOORD * 2; ++j)
            if (sum[i][j] - (i - k ? sum[i - k - 1][j] : 0) - (j - k ? sum[i][j - k - 1] : 0) + (i - k && j - k ? sum[i - k - 1][j - k - 1] : 0) == (k + 1) * (k + 1)) {
                //printf("%d %d\n", i - k - COORD_OFFSET, j - k - COORD_OFFSET);
                if (!f[i - k][j - k]) return false;
            }
    return true;
}

int maxSteps(std::vector<int> x, std::vector<int> y) {
    for (int &val : x) val += COORD_OFFSET;
    for (int &val : y) val += COORD_OFFSET;

    int lo = 0, hi = MAXCOORD - 3, mid;
    while (lo < hi - 1) {
        mid = (lo + hi) >> 1;
        if (check_steps(x, y, mid)) lo = mid; else hi = mid;
    }
    return (lo >= MAXCOORD - 4 ? -1 : lo);
}

};

int main()
{
    DrawingPointsDivOne worker;
    printf("%d\n", worker.maxSteps({0, 3}, {0, 0}));
    printf("%d\n", worker.maxSteps({0, 2}, {0, 0}));
    printf("%d\n", worker.maxSteps({-70}, {3}));
    printf("%d\n", worker.maxSteps({-41,-40,1,-11,-32,-7,24,-11,49,-15,-22,20,-8,54,54,69,16,-30,36,-6,-30,40,64,20,-66, -37,-33,-18,-35,36,9,61,-43,45,5,60,-8,-58,65,-66,41,12,34,-11,-57,-38,46,63,-55,3}, {5,-24,-2,-4,23,14,1,70,-26,45,15,48,32,-41,54,-47,-67,-46,-9,-53,54,28,-61,11,53,68, -33,62,37,-8,-17,-17,48,19,-49,56,-41,16,17,-50,28,59,10,50,23,-16,56,31,-70,-44}));
    //printf("%d\n", worker.maxSteps({39, 39}, {50, 26}));
    //printf("%d\n", worker.maxSteps({27, -48, 22, 67, 65, 25, 64, 55, 52, 33, -46, -16}, {-8, 11, -56, 69, -43, -39, 5, -38, -61, 13, -16, 10}));
    printf("%d\n", worker.maxSteps({-10, 32, 55, -65}, {-57, -12, -53, 23}));
    //printf("%d\n", worker.maxSteps({55, 2, 55}, {-25, 4, -8}));
    return 0;
}
