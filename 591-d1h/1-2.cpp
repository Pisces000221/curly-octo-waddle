#include <cstdio>
#include <algorithm>
#include <string>

class StringPath {
public:

typedef long long int64;
static const int MAXN = 8;
static const int ALPHABET = 26;
static const int MODULUS = 1e9 + 9;
#define _  %  MODULUS
#define __ %= MODULUS

inline int row_begin(int n, int m, int i) { return std::max(i - n + 1, 0); }
inline int row_end(int n, int m, int i) { return std::min(i, m - 1); }

int countBoards(int n, int m, std::string A, std::string B) {
    if (n > m) std::swap(n, m);

    static int64 f[MAXN * 2][MAXN][1 << (MAXN + 1)][1 << (MAXN + 1)];
    std::fill(&f[0][0][0][0], &f[0][0][0][0] + (sizeof f / sizeof f[2][3][3][3]), 0);
    if (A[0] == B[0]) {
        f[0][0][0][0] = ALPHABET - 1;
        f[0][0][1][1] = 1;
    } else {
        f[0][0][0][0] = ALPHABET - 2;
        f[0][0][0][1] = f[0][0][1][0] = 1;
    }
    int max_mask = (1 << (MAXN + 1)) - 1;
    for (int i = 0; i < n + m - 1; ++i) {
        for (int j = (i == 0 ? 1 : 0); j < MAXN; ++j) {
            int last_i = (j == 0 ? i - 1 : i),
                last_j = (j == 0 ? MAXN - 1 : j - 1);
            int64 contrib;
            if (j >= row_begin(n, m, i) && j <= row_end(n, m, i)) {
                for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB) if ((contrib = f[last_i][last_j][mA][mB]) > 0) {
                        if (A[i] == B[i]) {
                            // (1) New character == A[i]
                            (f[i][j][(mA << 1) & max_mask | (j && (mA & (1 << MAXN)) || (mA & (1 << (MAXN - 1))))][(mB << 1) & max_mask | (j && (mB & (1 << MAXN)) || (mB & (1 << (MAXN - 1))))] += contrib)__;
                            // (2) New character != A[i]
                            (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] += contrib * (ALPHABET - 1))__;
                        } else {
                            // (1) New character == A[i]
                            (f[i][j][(mA << 1) & max_mask | (j && (mA & (1 << MAXN)) || (mA & (1 << (MAXN - 1))))][(mB << 1) & max_mask] += contrib)__;
                            // (2) New character == B[i]
                            (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask | (j && (mB & (1 << MAXN)) || (mB & (1 << (MAXN - 1))))] += contrib)__;
                            // (3) New character != A[i], != B[i]
                            (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] += contrib * (ALPHABET - 2))__;
                        }
                    }
                /*for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB)
                        if (f[i][j][mA][mB]) printf("%d %d %d %d %lld\n", i, j, mA, mB, f[i][j][mA][mB]);*/
            } else {
                for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB)
                        (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] += f[last_i][last_j][mA][mB])__;
            }
        }
    }

    int64 ans = 0;
    for (int i = 0; i <= 1; ++i)
        for (int j = 0; j <= 1; ++j)
            ans += f[n + m - 2][m - 1][1 + i * (1 << MAXN)][1 + j * (1 << MAXN)];
    return (int)ans;
}

#undef _
#undef __
};

int main()
{
    StringPath worker;
    printf("%d\n", worker.countBoards(2, 2, "ABC", "ADC"));
    printf("%d\n", worker.countBoards(2, 2, "ABC", "ABD"));
    printf("%d\n", worker.countBoards(3, 4, "ABCDDE", "ACCBDE"));
    printf("%d\n", worker.countBoards(8, 8, "ZZZZZZZZZZZZZZZ", "ZABCDEFGHIJKLMZ"));
    //printf("%d\n", worker.countBoards(4, 6, "ABACABABA", "ADDDABCCA"));
    return 0;
}
