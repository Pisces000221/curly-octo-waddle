#include <cstdio>
#include <cstring>
typedef long long int64;

class PenguinEmperor {
public:

static const int MODULUS = 1e9 + 7;
#define _ % MODULUS
#define __ %= MODULUS

struct Matrix {
    static const int SZ = 354;
    int64 val[SZ][SZ];
    Matrix() { this->reset(); }
    inline void reset() { memset(val, 0, sizeof val); }
    inline void identity() { this->reset(); for (int i = 0; i < SZ; ++i) this->val[i][i] = 1; }
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

inline void moveOn(Matrix &mat, int n, int steps) {
    static Matrix next;
    next.reset();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            (next.val[i][(j + steps) % n] += mat.val[i][j])__;
            if ((steps * 2) % n != 0) (next.val[i][(j - steps + n) % n] += mat.val[i][j])__;
        }
    mat.assign(next);
}

int countJourneys(int numCities, int64 daysPassed) {
    static Matrix state, transition;
    state.identity();
    for (int i = 0; i < daysPassed % numCities; ++i) moveOn(state, numCities, i + 1);
    transition.assign(state);
    for (int i = daysPassed % numCities; i < numCities; ++i) moveOn(transition, numCities, i + 1);
    /*for (int i = 0; i < numCities; ++i)
        for (int j = 0; j < numCities; ++j)
            printf("%lld%c", transition.val[i][j], j == numCities - 1 ? '\n' : ' ');*/
    transition ^= (daysPassed / numCities);
    state *= transition;
    return state.val[0][0];
}

};

int main()
{
    PenguinEmperor worker;
    printf("%d\n", worker.countJourneys(3, 2));
    printf("%d\n", worker.countJourneys(4, 3));
    printf("%d\n", worker.countJourneys(5, 36));
    printf("%d\n", worker.countJourneys(300, 751));
    printf("%d\n", worker.countJourneys(350, 1000000000000000000)); // Time out > <
    return 0;
}
