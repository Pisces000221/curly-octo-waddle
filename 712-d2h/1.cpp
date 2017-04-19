#include <cstdio>
#include <algorithm>
#include <vector>

class AverageVarianceSubset {
public:

typedef long long int64;
static const int MAXN = 52;

double average(std::vector<int> s, int R) {
    std::sort(s.begin(), s.end());
    int n = s.size();
    if (n == 1) return 0.0;

    int subset_cnt = 0;
    double var_sum = 0;
    int lf_sz = n - n / 2, rg_sz = n / 2;

    return var_sum / subset_cnt;
}

};

int main()
{
    AverageVarianceSubset worker;
    printf("%.4lf\n", worker.average({1,2,3}, 1));
    printf("%.4lf\n", worker.average({1,2,3}, 3));
    printf("%.4lf\n", worker.average({5,1,3,2}, 1000000000));
    printf("%.4lf\n", worker.average({1,11,111,1111,11111,111111,1111111,11111111,111111111}, 123456));
    return 0;
}
