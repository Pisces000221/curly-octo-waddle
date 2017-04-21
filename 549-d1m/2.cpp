#include <cstdio>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

class MagicalHats {
public:

static const int MAXN = 15;
static const int INF = 0x3fffffff;

int n, m, numGuesses;
std::vector<std::pair<int, int>> hats;

static const int MAX_STATES = 1600000;
bool valid[MAX_STATES];
int mem[MAX_STATES];

// 2 - Unveiled, has coin
// 1 - Unveiled, no coin
// 0 - Veiled
inline int get(int mask, int pos) { while (pos--) mask /= 3; return mask % 3; }
inline int set(int mask, int pos, int val) {
    int stack = 0, p0s = pos;
    while (pos--) stack = stack * 3 + mask % 3, mask /= 3;
    mask = (mask / 3) * 3 + val;
    while (p0s--) mask = mask * 3 + stack % 3, stack /= 3;
    return mask;
}

int calc(int dep, int mask) {
    if (dep >= numGuesses) return 0;
    if (mem[mask] != INF) return mem[mask];

    int ans = -INF, cur, next_mask;
    // Player decides which hat to choose
    for (int i = 0; i < hats.size(); ++i) if (get(mask, i) == 0) {
        cur = INF;
        // Magician decides how to place the coins
        if (valid[next_mask = set(mask, i, 1)]) {
            cur = std::min(cur, calc(dep + 1, next_mask));
        }
        if (valid[next_mask = set(mask, i, 2)]) {
            cur = std::min(cur, calc(dep + 1, next_mask) + 1);
        }
        if (cur <= INF / 2) ans = std::max(ans, cur);
        //printf("Next_Mask = %d, Valid = %d\n", set(mask, i, 1), !invalid_state(mask));
    }
    //for (int p = 0; p < hats.size(); ++p) printf("%d ", get(mask, p)); printf("| %d\n", ans);
    return (mem[mask] = ans);
}

int findMaximumReward(std::vector<std::string> board, std::vector<int> coins, int numGuesses) {
    n = board.size(), m = board[0].length();
    this->numGuesses = numGuesses;
    hats.clear();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] == 'H') hats.push_back({ i, j });

    // Find out valid states, i.e. there exists a way to put coins into 0's that make up a valid board
    // Complexity is Binom(hats.size(), coins.size()) * 2^(hats.size()) * hats.size()
    std::fill(valid, valid + MAX_STATES, false);
    static bool row_parity[MAXN], col_parity[MAXN];
    for (int i = 0; i < (1 << hats.size()); ++i) if (__builtin_popcount(i) == coins.size()) {
        std::fill(row_parity, row_parity + n, false);
        std::fill(col_parity, col_parity + m, false);
        int mask = 0;
        for (int j = 0; j < hats.size(); ++j) {
            mask = set(mask, j, (i & (1 << j)) ? 2 : 1);
            if (!(i & (1 << j))) {
                row_parity[hats[j].first] ^= 1;
                col_parity[hats[j].second] ^= 1;
            }
        }
        bool so_far_valid = true;
        for (int i = 0; i < n; ++i) if (row_parity[i]) { so_far_valid = false; break; }
        for (int i = 0; i < m; ++i) if (col_parity[i]) { so_far_valid = false; break; }
        if (!so_far_valid) continue;
        //for (int p = 0; p < hats.size(); ++p) printf("%d%c", get(mask, p), p == hats.size() - 1 ? '\n' : ' ');
        for (int j = 0; j < (1 << hats.size()); ++j) {
            int cur = 0;
            for (int k = 0; k < hats.size(); ++k)
                if (j & (1 << k)) cur = set(cur, k, get(mask, k));
            //if (!valid[cur])
            //    for (int p = 0; p < hats.size(); ++p) printf("%d%c", get(cur, p), p == hats.size() - 1 ? '\n' : ' ');
            valid[cur] = true;
        }
    }

    // DP
    std::fill(mem, mem + MAX_STATES, 0x3fffffff);
    int max_coin_ct = calc(0, 0), ans = 0;
    if (max_coin_ct < 0) return -1;
    std::sort(coins.begin(), coins.end());
    for (int i = 0; i < max_coin_ct; ++i) ans += coins[i];
    return ans;
}

};

int main()
{
    MagicalHats worker;
    /*printf("%d\n", worker.findMaximumReward({"HHH", "H.H", "HH."}, {9}, 1));
    printf("%d\n", worker.findMaximumReward({"HH", "HH"}, {1,2,3,4}, 3));
    printf("%d\n", worker.findMaximumReward({"HHH", "HHH", "H.H"}, {13,13,13,13}, 2));
    printf("%d\n", worker.findMaximumReward({"HHH", "HHH", "H.H"}, {13,13,13,13}, 3));
    printf("%d\n", worker.findMaximumReward({"HHH", "H.H", "HHH", "H.H", "HHH"}, {33,337,1007,2403,5601,6003,9999}, 5))*/;

    printf("%d\n", worker.findMaximumReward({".H.H.H.H.", "H.H.H.H.H", ".H.H.H.H."}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, 9));  // Case #26
    //printf("%d\n", worker.findMaximumReward({".H.H.H.H.", "H.H.H.H.H", ".H.H.H.H."}, {9, 9, 9, 9, 9, 11, 11, 11, 11}, 6));  // Case #29
    return 0;
}
