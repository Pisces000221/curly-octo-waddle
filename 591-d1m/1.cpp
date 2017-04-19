#include <cstdio>

class PyramidSequences {
public:

typedef long long int64;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int64 distinctPairs(int N, int M) {
    --N, --M;
    int g = gcd(N, M);
    N /= g, M /= g;
    return ((int64)(N + 1) * (M + 1) + 1) / 2 + (int64)N * M * (g - 1);
}

};

int main()
{
    PyramidSequences worker;
    printf("%lld\n", worker.distinctPairs(3, 4));
    printf("%lld\n", worker.distinctPairs(3, 5));
    printf("%lld\n", worker.distinctPairs(43, 76));
    printf("%lld\n", worker.distinctPairs(2, 1000000000));
    printf("%lld\n", worker.distinctPairs(100000, 95555));
    return 0;
}
