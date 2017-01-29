#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
typedef long long int64;

class TheBrickTowerHardDivOne {
public:

static const int MODULUS = 1234567891;
static const int MAXK = 7;
#define _ % MODULUS
#define __ %= MODULUS

struct Matrix {
    static const int SZ = 256;
    int64 val[SZ][SZ];
    Matrix() { this->reset(); }
    inline void reset() { memset(val, 0, sizeof val); }
    inline void identity() { this->reset(); for (int i = 0; i < SZ; ++i) this->val[i][i] = 1; }
    inline void identity_ur() { for (int i = 0; i < SZ / 2; ++i) this->val[i][i + SZ / 2] = 1; }
    inline void identity_lr() { for (int i = 0; i < SZ / 2; ++i) this->val[i + SZ / 2][i + SZ / 2] = 1; }
    inline void assign(const Matrix &other) { memcpy(this->val, other.val, sizeof val); }

    inline void operator *= (const Matrix &other) {
        static Matrix ans;
        ans.reset();
        for (int i = 0; i < SZ; ++i)
            for (int j = 0; j < SZ; ++j) {
                ans.val[i][j] = 0;
                for (int k = 0; k < SZ; ++k)
                    (ans.val[i][j] += this->val[i][k] * other.val[k][j])__;
            }
        this->assign(ans);
    }

    inline void operator ^= (int64 exp) {
        static Matrix ans;
        ans.identity();
        for (; exp; exp >>= 1) {
            if (exp & 1) ans *= (*this); (*this) *= (*this);
        }
        this->assign(ans);
    }
};

int C;

static constexpr int COLOUR_CONFIGS[15][4] = {
    {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
    {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
    {0, 0, 1, 2}, {0, 1, 0, 2}, {0, 1, 2, 0},
    {0, 1, 1, 2}, {0, 1, 2, 1}, {0, 1, 2, 2}, {0, 1, 2, 3}
};
inline bool check_isomorphism(const int a[4], const int b[4]) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if ((a[i] == a[j]) ^ (b[i] == b[j])) return false;
    return true;
}
inline int col_config_id(const int a[4]) {
    for (int i = 0; i < 15; ++i) if (check_isomorphism(a, COLOUR_CONFIGS[i])) return i;
    assert(false);
}
inline int row_id(int col_cfg_id, int neighbouring) {
    return col_cfg_id * (MAXK + 1) + neighbouring;
}
inline int inter_pairs(const int col_config[4]) {
    return (int)
        (col_config[0] == col_config[1]) + (col_config[0] == col_config[2]) +
        (col_config[1] == col_config[2]) + (col_config[1] == col_config[3]);
}
inline int exter_pairs(const int a[4], const int b[4]) {
    return (int)(a[0] == b[0]) + (a[1] == b[1]) + (a[2] == b[2]) + (a[3] == b[3]);
}
inline std::map<int, int> num_setups(int lw, int up) {
    std::map<int, int> ret;
    // TODO: BEAT THIS
    return ret;
}

int find(int C, int K, int64 H) {
    this->C = C;

    //int a[4] = {{10, 2}, {3, 2}}; printf("%d\n", col_config_id(a));
    Matrix transition, state;
    transition.reset();
    for (int cfg = 0; cfg < 15; ++cfg) {
        for (int nxt = 0; nxt < 15; ++nxt) {
            auto xm = num_setups(cfg, nxt); // TODO: Give a proper name
            for (auto kv : xm) {
                for (int k = 0; k <= K; ++k)
                    if (k + kv.first <= K)
                        (transition.val[row_id(cfg, k)][row_id(nxt, k + kv.first)] += kv.second)__;
            }
        }
    }
    //  [ A | I ]^k     [ A^k | Sum ]
    //  [ 0 | I ]    =  [  0  |  I  ]
    transition.identity_ur();
    transition.identity_lr();
    transition ^= H;

    state.reset();
    state.identity();
    state *= transition;
    int64 ans = 0;
    for (int i = 0; i < 15; ++i)
        for (int k = 0; k <= K; ++k) (ans += state.val[0][row_id(i, k)])__;
    return ans;
}

#undef _
#undef __
};

constexpr int TheBrickTowerHardDivOne::COLOUR_CONFIGS[15][4];

int main()
{
    TheBrickTowerHardDivOne worker;
    printf("%d\n", worker.find(2, 0, 2));
    printf("%d\n", worker.find(1, 7, 19));
    printf("%d\n", worker.find(2, 3, 1));
    printf("%d\n", worker.find(4, 7, 47));
    return 0;
}
