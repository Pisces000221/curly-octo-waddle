#include <cstdio>
#include <map>
typedef long long int64;

class TheDivisionGame {
public:

static const int MAXL = 1e9 + 2;
static const int MAXL_SQRT = 3.5e4 + 2;
static const int MAX_PRIMES = 4096; // 3732

int primes[MAX_PRIMES], prime_ct = 0;
bool not_prime[MAXL_SQRT] = { false };
inline void sieve() {
    not_prime[0] = not_prime[1] = true;
    for (int i = 2; i < MAXL_SQRT; ++i) {
        if (!not_prime[i]) primes[prime_ct++] = i;
        for (int j = 0; j < prime_ct && (int64)i * primes[j] < MAXL_SQRT; ++j)
            not_prime[i * primes[j]] = true;
    }
    //printf("%d\n", prime_ct);
}

inline int prime_factors(int x) {
    int ans = 0;
    for (int i = 0; i < prime_ct; ++i)
        while (x % primes[i] == 0) { x /= primes[i]; ++ans; }
    if (x > 1) ++ans;
    return ans;
}

int64 countWinningIntervals(int L, int R) {
    if (prime_ct == 0) sieve();
    std::map<int, int> counter;
    int sg = 0;
    for (int i = L; i <= R; ++i) ++counter[sg ^= prime_factors(i)];
    ++counter[0];
    int64 ans = 0;
    for (auto kv : counter) {
        ans += (int64)kv.second * (kv.second - 1) / 2;
    }
    return (int64)(R - L + 1) * (R - L + 2) / 2 - ans;
}

};

int main()
{
    TheDivisionGame worker;
    printf("%lld\n", worker.countWinningIntervals(9, 10));
    printf("%lld\n", worker.countWinningIntervals(2, 5));
    printf("%lld\n", worker.countWinningIntervals(2, 6));
    printf("%lld\n", worker.countWinningIntervals(2, 100));
    printf("%lld\n", worker.countWinningIntervals(1e9, 1e9 + 1e6)); // TLE (つД`)
    return 0;
}
