#include <cstdio>
#include <algorithm>
#include <string>

class StringPath {
public:

typedef long long int64;
static const int MAXN = 5;//8;
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
            if (j >= row_begin(n, m, i) && j <= row_end(n, m, i)) {
                //printf("%d %d\n", i, j);
                for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB) if (f[last_i][last_j][mA][mB] > 0) {
                        //printf("%d %d %d %d %lld\n", last_i, last_j, mA, mB, f[last_i][last_j][mA][mB]);
                        if (A[i] == B[i]) {
                            (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] += f[last_i][last_j][mA][mB] * (ALPHABET - 1))__;
                            (f[i][j][(mA << 1) & max_mask | 1][(mB << 1) & max_mask | 1] += f[last_i][last_j][mA][mB] * 1)__;
                        } else {
                            (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] += f[last_i][last_j][mA][mB] * (ALPHABET - 2))__;
                            (f[i][j][(mA << 1) & max_mask | 1][(mB << 1) & max_mask] += f[last_i][last_j][mA][mB] * 1)__;
                            (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask | 1] += f[last_i][last_j][mA][mB] * 1)__;
                        }
                    }
                for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB)
                        if (f[i][j][mA][mB]) printf("%d %d %d %d %lld\n", i, j, mA, mB, f[i][j][mA][mB]);
            } else {
                //printf("%d %d - %d %d\n", last_i, last_j, i, j);
                //for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                //    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB)
                //        f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] = f[last_i][last_j][mA][mB], (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] && printf("%d %d %d %d - %d %d %d %d %lld *\n", last_i, last_j, mA, mB, i, j, (mA << 1) & max_mask, (mB << 1) & max_mask, f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask]));
                        //, (f[i][j][mA][mB] && printf("%d %d %d %d %lld *\n", i, j, mA, mB, f[i][j][mA][mB]));
                for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB)
                        (f[i][j][(mA << 1) & max_mask][(mB << 1) & max_mask] += f[last_i][last_j][mA][mB])__;
                        //, (f[i][j][mA][mB] && printf("%d %d %d %d %lld *\n", i, j, mA, mB, f[i][j][mA][mB]));
                /*for (int mA = 0; mA < (1 << (MAXN + 1)); ++mA)
                    for (int mB = 0; mB < (1 << (MAXN + 1)); ++mB)
                        if (f[i][j][mA][mB]) printf("%d %d %d %d %lld\n", i, j, mA, mB, f[i][j][mA][mB]);*/
            }
        }
    }

    return (int)f[n + m - 2][m - 1][1][1];
}

#undef _
#undef __
};

int main()
{
    StringPath worker;
    printf("%d\n", worker.countBoards(2, 2, "ABC", "ADC"));
    /*printf("%d\n", worker.countBoards(2, 2, "ABC", "ABD"));
    printf("%d\n", worker.countBoards(3, 4, "ABCDDE", "ACCBDE"));
    printf("%d\n", worker.countBoards(8, 8, "ZZZZZZZZZZZZZZZ", "ZABCDEFGHIJKLMZ"));*/
    //printf("%d\n", worker.countBoards(4, 6, "ABACABABA", "ADDDABCCA"));
    return 0;
}
