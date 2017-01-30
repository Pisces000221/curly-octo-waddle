#include <cstdio>
#include <cstring>
typedef long long int64;

class PenguinEmperor {
public:

static const int MAXN = 354;
static const int MODULUS = 1e9 + 7;
#define _ % MODULUS
#define __ %= MODULUS

inline void moveOn(int *trans, int n, int steps) {
    static int next[MAXN];
    memset(next, 0, n * sizeof(int));
    for (int j = 0; j < n; ++j) {
        (next[(j + steps) % n] += trans[j])__;
        if ((steps * 2) % n != 0) (next[(j - steps + n) % n] += trans[j])__;
    }
    memcpy(trans, next, n * sizeof(int));
}
inline void combine(int *trans, int *other, int n) {
    static int next[MAXN];
    memset(next, 0, n * sizeof(int));
    for (int i = 0; i < n; ++i) if (other[i]) {
        for (int j = 0; j < n; ++j) {
            next[(j - i + n) % n] = ((int64)next[(j - i + n) % n] + (int64)trans[j] * other[i])_;
        }
    }
    memcpy(trans, next, n * sizeof(int));
}

int countJourneys(int numCities, int64 daysPassed) {
    static int state[MAXN], trans[MAXN];
    memset(state, 0, sizeof state); state[0] = 1;
    for (int i = 0; i < daysPassed % numCities; ++i) moveOn(state, numCities, i + 1);
    memcpy(trans, state, sizeof state);
    for (int i = daysPassed % numCities; i < numCities; ++i) moveOn(trans, numCities, i + 1);

    static int pow[MAXN];
    memset(pow, 0, sizeof pow); pow[0] = 1;
    for (int64 exp = daysPassed / numCities; exp; exp >>= 1) {
        if (exp & 1) combine(pow, trans, numCities); combine(trans, trans, numCities);
    }
    combine(state, pow, numCities);
    return state[0];
}

};

int main()
{
    PenguinEmperor worker;
    printf("%d\n", worker.countJourneys(3, 2));
    printf("%d\n", worker.countJourneys(4, 3));
    printf("%d\n", worker.countJourneys(5, 36));
    printf("%d\n", worker.countJourneys(300, 751));
    printf("%d\n", worker.countJourneys(350, 1000000000000000000));
    return 0;
}
