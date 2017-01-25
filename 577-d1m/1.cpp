#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

template <typename T> inline void upd_min(T &var, const T val) { if (var > val) var = val; }

class EllysChessboard {
public:

static const int INF = 0x7f7f7f7f;
static const int INF_BYTE = 0x7f;
static const int N = 8;
static const int R = 16;
// f[x_min][x_max][y_min][y_max]
int f[R][R][R][R];
int x[N * N], y[N * N], chess_ct;
bool outside[N * N];

int minCost(std::vector<std::string> board) {
    memset(f, 0x7f, sizeof f);
    chess_ct = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (board[i][j] == '#') {
                x[chess_ct] = i + j, y[chess_ct] = i - j + R/2 - 1;
                printf("%d %d\n", x[chess_ct], y[chess_ct]);
                f[x[chess_ct]][x[chess_ct]][y[chess_ct]][y[chess_ct]] = 0;
                ++chess_ct;
            }

    for (int dx = 0; dx < R; ++dx)
        for (int i = 0; i < R - dx; ++i)
            for (int dy = 0; dy < R; ++dy)
                for (int j = 0; j < R - dy; ++j) if (f[i][i + dx][j][j + dy] != INF) {
                    bool has_outside = false;
                    memset(outside, false, sizeof outside);
                    for (int p = 0; p < chess_ct; ++p)
                        if ((x[p] < i || x[p] > i + dx) || (y[p] < j || y[p] > j + dy))
                            outside[p] = has_outside = true;
                    if (!has_outside) return f[i][i + dx][j][j + dy];
                    printf("%d %d %d %d\n", i, i + dx, j, j + dy);
                    for (int p = 0; p < chess_ct; ++p) if (outside[p]) {
                        int x_min = std::min(i, x[p]), x_max = std::max(i + dx, x[p]),
                            y_min = std::min(j, y[p]), y_max = std::max(j + dy, y[p]);
                        int additional_cost = 0;
                        for (int q = 0; q < chess_ct; ++q)
                            if (outside[q] && x[q] >= x_min && x[q] <= x_max && y[q] >= y_min && y[q] <= y_max) {
                                additional_cost += std::max(std::max(x_max - x[q], x[q] - x_min), std::max(y_max - y[q], y[q] - y_min));
                            }
                        printf("\t→ %d %d %d %d with +%d\n", x_min, x_max, y_min, y_max, additional_cost);
                        upd_min(f[x_min][x_max][y_min][y_max], f[i][i + dx][j][j + dy] + additional_cost);
                    }
                }

    return 0;
}

};

int main()
{
    EllysChessboard worker;
    printf("%d\n", worker.minCost({"........", "........", "...#....", ".#......", ".......#", "........", "........", "........"}));
    printf("%d\n", worker.minCost({"........", "........", "........", "........", "........", "........", "........", "........"}));
    printf("%d\n", worker.minCost({".#......", "........", "..#..#.#", "...#..#.", "........", "...#...#", "...#...#", "........"}));
    return 0;
}
