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

    int64 subset_cnt = 0;
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

    printf("%.4lf\n", worker.average({546392386, 989939501, 138350642, 296751024, 511315675, 737741611, 364070805, 516045285, 340946329, 639018763, 5567688, 24109720, 808000925, 169150440, 913254493, 225242497, 4005195, 592394468, 513392111, 129856382, 568317331, 569671607, 697749142, 185671536, 652828828, 735149658, 960256764, 730150690, 162219083, 606024985, 204415228, 555126857, 608193692, 514250468, 223534483, 980890475, 425608006, 221908606, 2414882, 521893730, 899538350, 849151763, 991445587, 995744182, 575829776, 823233054, 961951786, 659945588, 565883473, 153396145}, 705032704));
    return 0;
}
