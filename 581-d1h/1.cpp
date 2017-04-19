#include <cstdio>
#include <string>
#include <vector>

class YetAnotherBoardGame {
public:

static const int MAXN = 13;

int n, m;
bool board[MAXN][MAXN];
int ans;

int col_op[MAXN];

inline void apply_op(int row, int col, int op) {
    static const int mov[5][2] = {{0, 0}, {-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
    for (int k = op; k < 5; ++k) {
        int nr = row + mov[k][0], nc = col + mov[k][1];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m) board[nr][nc] ^= 1;
    }
}

inline void dfs(int row, int cur_ans) {
    if (row == n) {
        bool valid = true;
        for (int i = 0; i < m; ++i)
            if (!board[n - 1][i]) { valid = false; break; }
        if (valid) ans = std::min(ans, cur_ans);
        return;
    }
    /*if (row <= 4) {
        printf("%d %d\n", row, cur_ans);
        for (int i = 0; i < m; ++i) putchar(col_op[i] == -1 ? ' ' : (col_op[i] == 0 ? 'o' : '*'));
        putchar('\n');
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) putchar(board[i][j] ? 'B' : 'W');
            putchar('\n');
        }
    }*/
    int row_op = -1;
    for (int i = 0; i < m; ++i) if (!board[row - 1][i] && col_op[i] != -1) {
        if (row_op == -1) row_op = col_op[i];
        else if (row_op != col_op[i]) return;
    }
    std::vector<int> pos;
    int prev_col_op[MAXN];
    for (int applied = (row_op == -1 ? 0 : row_op); applied <= (row_op == -1 ? 1 : row_op); ++applied) {
        pos.clear();
        for (int i = 0; i < m; ++i) prev_col_op[i] = col_op[i];
        for (int i = 0; i < m; ++i) if (!board[row - 1][i]) {
            pos.push_back(i);
            col_op[i] = applied;
            apply_op(row, i, applied);
        }
        //printf("> %d %d > RowOp = %d | Type %d\n", row, cur_ans, row_op, applied);
        dfs(row + 1, cur_ans + pos.size());
        for (int i : pos) apply_op(row, i, applied);
        for (int i = 0; i < m; ++i) col_op[i] = prev_col_op[i];
    }
}

int minimumMoves(std::vector<std::string> board) {
    n = board.size();
    m = board[0].length();

    ans = MAXN * MAXN * 114514;
    for (int op = 0; op <= 1; ++op) {
        for (int mask = 0; mask < (1 << m); ++mask) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j) this->board[i][j] = (board[i][j] == 'B');
            for (int i = 0; i < m; ++i)
                if (mask & (1 << i)) {
                    apply_op(0, i, op);
                    col_op[i] = op;
                } else {
                    col_op[i] = -1;
                }
            dfs(1, __builtin_popcount(mask));
        }
    }

    return (ans == MAXN * MAXN * 114514 ? -1 : ans);
}

};

int main()
{
    YetAnotherBoardGame worker;
    printf("%d\n", worker.minimumMoves({"BBBBBBBBB", "BBWBBBBBB", "BWWWBBBBB", "BBWBBBWBB", "BBBBBWBWB", "BBBBBBWBB"}));
    printf("%d\n", worker.minimumMoves({"BBW", "WWW", "BWW"}));
    printf("%d\n", worker.minimumMoves({"WBW", "BBW", "WBW"}));
    printf("%d\n", worker.minimumMoves({"BBBB", "WBWB", "BBBB", "BBBB"}));
    printf("%d\n", worker.minimumMoves({"WWWWWBW", "WBWBWBW", "BBWBBWW"}));
    printf("%d\n", worker.minimumMoves({"WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW", "WWWWWWWWWW"}));
    return 0;
}
