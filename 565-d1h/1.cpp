#include <cstdio>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>
typedef long long int64;

class UnknownTree {
public:

static const int MAXN = 51;
static const int MODULUS = 1000000009;
#define _ % MODULUS
#define __ %= MODULUS

inline int getCount_singlePivot(const std::vector<int> &distances) {
    int n = (int)distances.size();
    int64 ans = 1;
    for (int i = 0; i < n; ++i) {
        if (distances[i] < 0) return 0;
        int ct = 0;
        for (int j = 0; j < n; ++j) if (distances[j] < distances[i]) ++ct;
        (ans *= (ct + 1))__;
    }
    for (int x : distances) printf(" %d", x); printf(" | %lld\n", ans);
    return ans;
}

int getCount(std::vector<int> distA, std::vector<int> distB, std::vector<int> distC) {
    int n = (int)distA.size();
    int64 ans = 0;
    // Y-shaped solutions
    std::vector<int> spd[4];    // Single-pivot distances
    for (int i = 0; i < 4; ++i) spd[i].reserve(n + 5);
    for (int pvt = 0; pvt < n; ++pvt) {
        for (int i = 0; i < 4; ++i) spd[i].clear();
        int distPA = distA[pvt], distPB = distB[pvt], distPC = distC[pvt];
        int distAB = distPA + distPB, distBC = distPB + distPC, distCA = distPC + distPA;
        spd[0].push_back(distPA); spd[1].push_back(distPB); spd[2].push_back(distPC);
        bool valid = true;
        for (int i = 0; i < n; ++i) if (i != pvt) {
            int distIAB = distA[i] + distB[i] - distAB,
                distIBC = distB[i] + distC[i] - distBC,
                distICA = distC[i] + distA[i] - distCA;
            if (distIAB < 0 || distIBC < 0 || distICA < 0 || (distIAB & 1) || (distIBC & 1) || (distICA & 1)) { valid = false; break; }
            distIAB /= 2; distIBC /= 2; distICA /= 2;
            printf("Pivot = %d  I = %d / %d %d %d\n", pvt, i, distIAB, distIBC, distICA);
            if (distIAB == distIBC && distIBC == distICA) spd[3].push_back(distIAB);
            else if (distIAB == distIBC) spd[0].push_back(distPB - distB[i] + distIAB);
            else if (distIBC == distICA) spd[1].push_back(distPC - distC[i] + distIBC);
            else if (distICA == distIAB) spd[2].push_back(distPA - distA[i] + distICA);
            else {
                /*puts("(・・?)");*/ valid = false; break;
            }
        }
        if (valid) {
            int64 cur = 1;
            for (int i = 0; i < 4; ++i) (cur *= getCount_singlePivot(spd[i]))__;
            (ans += cur)__;
        }
    }
    return ans;
}

#undef _
#undef __
};

int main()
{
    UnknownTree worker;
    printf("0) %d\n", worker.getCount({1}, {2}, {3}));
    printf("1) %d\n", worker.getCount({1, 2}, {1, 2}, {1, 2}));
    printf("2) %d\n", worker.getCount({5, 4}, {3, 2}, {2, 1}));
    printf("3) %d\n", worker.getCount({2, 4, 2}, {1, 3, 3}, {4, 6, 4}));
    printf("4) %d\n", worker.getCount({4, 6, 1, 5, 3, 2, 5}, {4, 2, 3, 1, 3, 2, 1}, {5, 7, 2, 6, 4, 3, 6}));
    //printf("5) %d\n", worker.getCount({6, 4, 5, 6, 8, 1, 5, 6, 4, 2}, {4, 2, 3, 4, 6, 1, 3, 4, 2, 2}, {6, 4, 5, 6, 8, 3, 5, 6, 4, 4}));
    //printf("6) %d\n", worker.getCount({8, 5, 6, 8, 6, 5, 6, 10, 8, 5, 10, 8, 7, 9, 7, 1, 11, 5, 9, 6, 6, 1, 6, 9, 8, 4, 12, 7, 5, 7, 6, 8, 12, 8, 6, 6, 5, 8, 5, 3, 3, 4, 8, 6, 6, 8, 8, 9, 7, 5}, {9, 6, 7, 9, 7, 6, 7, 11, 9, 6, 11, 9, 8, 10, 8, 2, 12, 6, 10, 7, 7, 4, 7, 10, 9, 5, 13, 8, 6, 8, 7, 9, 13, 9, 7, 7, 6, 9, 6, 4, 4, 5, 9, 7, 7, 9, 9, 10, 8, 6}, {8, 9, 6, 8, 2, 5, 6, 10, 8, 5, 10, 8, 7, 9, 1, 5, 11, 5, 9, 6, 6, 7, 6, 9, 8, 4, 12, 7, 5, 7, 6, 8, 12, 8, 6, 6, 5, 8, 1, 7, 3, 4, 8, 6, 6, 8, 8, 3, 7, 5}));
    return 0;
}
