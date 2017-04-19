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

    int subset_cnt = 0;
    double var_sum = 0;

    int64 seg_cnt[MAXN];
    // sqr('s)_sum = Sum(x_i ^ 2)
    // sum('s)_sqr = Sum(x_i) ^ 2
    // sum = Sum(x_i)
    double sqr_sum[MAXN], sum_sqr[MAXN], sum[MAXN];
    int last_endpoint = -1;
    for (int i = 0; i < n; ++i) {
        std::fill(seg_cnt, seg_cnt + MAXN, 0);
        std::fill(sqr_sum, sqr_sum + MAXN, 0);
        std::fill(sum_sqr, sum_sqr + MAXN, 0);
        std::fill(sum, sum + MAXN, 0);
        seg_cnt[0] = 1;
        int j;
        for (j = i; j < n && s[j] - s[i] <= R; ++j) {
            for (int k = MAXN - 1; k >= 0; --k) if (seg_cnt[k]) {
                seg_cnt[k + 1] += seg_cnt[k];
                sqr_sum[k + 1] += sqr_sum[k] + (double)s[j] * s[j] * seg_cnt[k];
                sum_sqr[k + 1] += sum_sqr[k] + 2.0 * s[j] * sum[k] + (double)s[j] * s[j] * seg_cnt[k];
                sum[k + 1] += sum[k] + (double)s[j] * seg_cnt[k];

                if (j >= last_endpoint) {
                    subset_cnt += seg_cnt[k];
                    var_sum += (
                        // New Sum(x_i ^ 2)
                        sqr_sum[k] + (double)s[j] * s[j] * seg_cnt[k] +
                        // New Sum(x_i) ^ 2 multiplied by a coefficient
                        (sum_sqr[k] + 2.0 * s[j] * sum[k] + (double)s[j] * s[j] * seg_cnt[k]) * (1.0 / (k + 1) - 2.0 / (k + 1))
                    ) / (k + 1);
                }
            }
        }
        last_endpoint = j;
    }

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
    printf("%.4lf\n", worker.average({1}, 0));
    return 0;
}
