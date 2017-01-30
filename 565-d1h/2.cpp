#include <cstdio>
#include <cstdlib>
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

inline int getCount_singlePivot(std::vector<int> &distances) {
    std::sort(distances.begin(), distances.end());
    if (distances.front() != 0) return 0;
    int n = (int)distances.size();
    int64 ans = 1;
    for (int i = 1; i < n; ++i) {
        if (distances[i] < 0) return 0;
        int ct = 0;
        for (int j = 0; j < n; ++j) if (distances[j] < distances[i]) ++ct;
        (ans *= ct)__;
    }
    return ans;
}

// Y-shaped solutions
inline int64 getCount_allTriangles(const std::vector<int> &distA, const std::vector<int> &distB, const std::vector<int> &distC) {
    int n = (int)distA.size();
    int64 ans = 0;
    std::map<int, std::vector<int>> branchA, branchB, branchC;
    for (int pvt = 0; pvt < n; ++pvt) {
        branchA.clear(); branchB.clear(); branchC.clear();
        int distPA = distA[pvt], distPB = distB[pvt], distPC = distC[pvt];
        int distAB = distPA + distPB, distBC = distPB + distPC, distCA = distPC + distPA;
        branchA[distAB].push_back(0);
        branchB[distBC].push_back(0);
        branchC[distCA].push_back(0);
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            int diffAB = distA[i] - distB[i], diffBC = distB[i] - distC[i], diffCA = distC[i] - distA[i];
            if (diffAB == distPA - distPB && (distC[i] + distA[i] - distCA) % 2 == 0)
                branchC[-diffCA].push_back((distA[i] + distC[i] - distCA) / 2);
            else if (diffBC == distPB - distPC && (distA[i] + distB[i] - distAB) % 2 == 0)
                branchA[-diffAB].push_back((distA[i] + distB[i] - distAB) / 2);
            else if (diffCA == distPC - distPA && (distB[i] + distC[i] - distBC) % 2 == 0)
                branchB[-diffBC].push_back((distB[i] + distC[i] - distBC) / 2);
            else { valid = false; break; }
        }
        if (valid) {
            int64 cur = 1;
            for (auto kv : branchA)
                (cur *= (kv.first < distPB - distPA || kv.first > distAB || ((distAB - kv.first) & 1)) ? 0 : getCount_singlePivot(kv.second))__;
            for (auto kv : branchB)
                (cur *= (kv.first < distPC - distPB || kv.first > distBC || ((distBC - kv.first) & 1)) ? 0 : getCount_singlePivot(kv.second))__;
            for (auto kv : branchC)
                (cur *= (kv.first < distPA - distPC || kv.first > distCA || ((distCA - kv.first) & 1)) ? 0 : getCount_singlePivot(kv.second))__;
            (ans += cur)__;
        }
    }
    return ans;
}

inline int64 getCount_orderedChainDist(const std::vector<int> &distA, const std::vector<int> &distB, const std::vector<int> &distC, int distAB, int distAC) {
    if (distAB == 0 || distAC == 0) return 0;
    int n = (int)distA.size();
    std::map<int, std::vector<int>> branchB, branchC;
    branchB[distAB].push_back(0);
    branchB[-distAB].push_back(0);
    branchC[-distAC].push_back(0);
    for (int i = 0; i < n; ++i) {
        int diffAB = distB[i] - distA[i], diffAC = distC[i] - distA[i];
        if (diffAC == distAC && (distA[i] + distB[i] - distAB) % 2 == 0)
            branchB[diffAB].push_back((distA[i] + distB[i] - distAB) / 2);
        else if (diffAB == distAB && (distA[i] + distC[i] - distAC) % 2 == 0)
            branchC[diffAC].push_back((distA[i] + distC[i] - distAC) / 2);
        else return 0;
    }
    int64 cur = 1;
    for (auto kv : branchB)
        (cur *= (kv.first < -distAB || kv.first > distAB || ((kv.first + distAB) & 1)) ? 0 : getCount_singlePivot(kv.second))__;
    for (auto kv : branchC)
        (cur *= (kv.first < -distAC || kv.first > distAC || ((kv.first + distAC) & 1)) ? 0 : getCount_singlePivot(kv.second))__;
    return cur;
}

// Chain-shaped solutions
inline int64 getCount_orderedChain(const std::vector<int> &distA, const std::vector<int> &distB, const std::vector<int> &distC) {
    int p = std::min_element(distA.begin(), distA.end()) - distA.begin();
    // Four cases
    return (
        getCount_orderedChainDist(distA, distB, distC, distA[p] + distB[p], distA[p] + distC[p]) +
        getCount_orderedChainDist(distA, distB, distC, distA[p] + distB[p], std::abs(distA[p] - distC[p])) +
        getCount_orderedChainDist(distA, distB, distC, std::abs(distA[p] - distB[p]), distA[p] + distC[p]) +
        getCount_orderedChainDist(distA, distB, distC, std::abs(distA[p] - distB[p]), std::abs(distA[p] - distC[p])))_;
}

int getCount(std::vector<int> distA, std::vector<int> distB, std::vector<int> distC) {
    return (getCount_allTriangles(distA, distB, distC) +
        getCount_orderedChain(distA, distB, distC) +
        getCount_orderedChain(distB, distC, distA) +
        getCount_orderedChain(distC, distA, distB))_;
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
    printf("5) %d\n", worker.getCount({6, 4, 5, 6, 8, 1, 5, 6, 4, 2}, {4, 2, 3, 4, 6, 1, 3, 4, 2, 2}, {6, 4, 5, 6, 8, 3, 5, 6, 4, 4}));
    printf("6) %d\n", worker.getCount({8, 5, 6, 8, 6, 5, 6, 10, 8, 5, 10, 8, 7, 9, 7, 1, 11, 5, 9, 6, 6, 1, 6, 9, 8, 4, 12, 7, 5, 7, 6, 8, 12, 8, 6, 6, 5, 8, 5, 3, 3, 4, 8, 6, 6, 8, 8, 9, 7, 5}, {9, 6, 7, 9, 7, 6, 7, 11, 9, 6, 11, 9, 8, 10, 8, 2, 12, 6, 10, 7, 7, 4, 7, 10, 9, 5, 13, 8, 6, 8, 7, 9, 13, 9, 7, 7, 6, 9, 6, 4, 4, 5, 9, 7, 7, 9, 9, 10, 8, 6}, {8, 9, 6, 8, 2, 5, 6, 10, 8, 5, 10, 8, 7, 9, 1, 5, 11, 5, 9, 6, 6, 7, 6, 9, 8, 4, 12, 7, 5, 7, 6, 8, 12, 8, 6, 6, 5, 8, 1, 7, 3, 4, 8, 6, 6, 8, 8, 3, 7, 5}));
    return 0;
}
