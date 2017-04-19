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
                    double p = var_sum;
                    printf("%.4lf\n", sum_sqr[k] + 2.0 * s[j] * sum[k] + (double)s[j] * s[j] * seg_cnt[k]);
                    printf("%.4lf\n", (double)seg_cnt[k] / (k + 1) / (k + 1));
                    var_sum += (
                        // New Sum(x_i ^ 2)
                        sqr_sum[k] + (double)s[j] * s[j] * seg_cnt[k] +
                        // New Sum(x_i) ^ 2 multiplied by a coefficient
                        //(sum_sqr[k] + 2.0 * s[j] * sum[k] + (double)s[j] * s[j] * seg_cnt[k]) * (-2.0 / (k + 1) + (double)seg_cnt[k] / (k + 1) / (k + 1))
                        (sum_sqr[k] + 2.0 * s[j] * sum[k] + (double)s[j] * s[j] * seg_cnt[k]) * (1.0 / (k + 1) - 2.0 / (k + 1))
                    ) / (k + 1);
                    //printf("[%d,%d] Sz=%d Contrib = %.4lf\n", i, j, k + 1, (sqr_sum[k] + (double)s[j] * s[j] * seg_cnt[k] + (2.0 * s[j] * sum[k] + (double)s[j] * s[j] * seg_cnt[k] + sum_sqr[k]) * (-2.0 / (k + 1) + 1.0 / (k + 1) / (k + 1))) / (k + 1));
                    //printf("[%d,%d] Sz=%d Contrib = %.4lf\n", i, j, k + 1, (5.0 + 9.0 * (-2.0 / (k + 1) + 1.0 / (k + 1) / (k + 1))) / (k + 1));
                    printf("[%d,%d] Sz=%d Contrib = %.4lf\n", i, j, k + 1, var_sum - p);
                }
            }
        }
        last_endpoint = j;
        printf("== [%d,%d] ==\n", i, j - 1);
        for (int k = 0; k < MAXN; ++k)
            if (seg_cnt[k]) printf("%2d | Ct = %lld, Sum = %d, Sum(x^2) = %d, Sum(x)^2 = %d\n", k, seg_cnt[k], (int)sum[k], (int)sqr_sum[k], (int)sum_sqr[k]);
    }

    printf("%d\n", subset_cnt);
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
