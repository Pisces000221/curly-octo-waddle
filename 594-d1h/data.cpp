#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
    unsigned int seed = (unsigned)time(NULL);
    fprintf(stderr, "Seed: %u\n", seed);
    srand(seed);

    int T; scanf("%d", &T);
    while (T--) {
        int n = rand() % 100 + 10;
        printf("%d %d %d\n", n, rand() % (n / 4) + 1, rand() % n + 1);
    }

    return 0;
}
