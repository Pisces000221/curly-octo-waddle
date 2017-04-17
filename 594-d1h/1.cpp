#include <cstdio>
#include <algorithm>

class FoxAndAvatar {
public:

static const int MAXN = 3004;

inline int rem(int a, int b) { return (a % b == 0 ? b : a % b); }

inline bool checkFeasibility(int S, int n, int w, int x) {
    //printf("%d %d %d %d\n", S, n, w, x);
    if (n <= 0 || x <= 0) { puts("> <"); return false; }
    switch (S) {
        case 0: return (n == 1 && w == 1 && x == 1);
        case 1:
            return
                (n <= w && (x == 1 || x == n)) ||
                (n % w == 1 && x == n) ||
                (w == 1 && (x == 1 || x == n)) ||
                (n < 2 * w && x == w);
        case 2: case 3: {
            int x_row = (x - 1) / w + 1;
            int n_row = (n - 1) / w;
            //printf("x = %d, w = %d -> x_row = %d, x %% w = %d\n", x, w, x_row, x % w);
            // (1) Down
            if (w * x_row < n && checkFeasibility(S - 1, w * x_row, w, x)) return true;
            // (2) Up
            for (int i = 1; i <= w; ++i)
                for (int j = 1; j < x_row; ++j) {
                    //printf("(Up Rm %d*%d) Check(%d, %d, %d, %d) - Check(%d, %d, %d, %d)\n", i, j, S, n, w, x, S - 1, n - i * j, w, x - i * j);
                    if (checkFeasibility(S - 1, n - i * j, w, x - i * j)) return true;
                }
            // (3) Left
            for (int i = 1; i < rem(x, w); ++i)
                for (int j = 0; j < x_row; ++j) {
                    //printf("(Lf Rm %d*%d) Check(%d, %d, %d, %d) - Check(%d, %d, %d, %d)\n", i, j, S, n, w, x, S - 1, n - i * (n_row - j) - std::min(rem(n, w), i), w, x - i * (x_row - j));
                    if (checkFeasibility(S - 1, n - i * (n_row - j) - std::min(rem(n, w), i), w, x - i * (x_row - j)))
                        return true;
                }
            // (4) Right
            for (int i = 1; i <= w - rem(x, w); ++i)
                for (int j = 0; j < x_row; ++j) {
                    //printf("(Rg Rm %d*%d) Check(%d, %d, %d, %d) - Check(%d, %d, %d, %d)\n", i, j, S, n, w, x, S - 1, n - i * (n_row - j) - std::max(0, std::min(rem(n, w) - rem(x, w), i)), w, x - i * (x_row - j - 1));
                    if (checkFeasibility(S - 1, n - i * (n_row - j) - std::max(0, std::min(rem(n, w) - rem(x, w), i)), w, x - i * (x_row - j - 1)))
                        return true;
                }
            return false;
        }
        case 4:
            return true;
        default: puts("O O"); return true;
    }
}

int minimalSteps(int n, int w, int x) {
    for (int i = 0; ; ++i)
        if (checkFeasibility(i, n, w, x)) return i;
}

};

int main()
{
    FoxAndAvatar worker;
    /*while (true) {
        int n, w, x;
        if (scanf("%d%d%d", &n, &w, &x) != 3) break;
        printf("%d\n", worker.minimalSteps(n, w, x));
    }*/

    printf("%d\n", worker.minimalSteps(3, 2, 3));
    printf("%d\n", worker.minimalSteps(5, 2, 3));
    printf("%d\n", worker.minimalSteps(13, 3, 8));
    printf("%d\n", worker.minimalSteps(54, 6, 28));
    printf("%d\n", worker.minimalSteps(1, 1, 1));

    printf("%d\n", worker.minimalSteps(40, 6, 28));
    printf("%d\n", worker.minimalSteps(26, 6, 18));
    printf("%d\n", worker.minimalSteps(30, 6, 18));
    printf("%d\n", worker.minimalSteps(51, 6, 22));
    printf("%d\n", worker.minimalSteps(37, 6, 18));
    return 0;
}
