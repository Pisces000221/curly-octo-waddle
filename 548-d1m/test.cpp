#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <utility>
#include <vector>
#define ll long long
using namespace std;
const int maxn=55;

class KingdomAndDice_ac{
	int cnt[maxn];
	int dp[maxn*maxn],f[maxn*maxn];
	int n,m;
	public:
	double newFairness(vector <int> firstDie, vector <int> secondDie, int X){
		sort(firstDie.begin(),firstDie.end());
		sort(secondDie.begin(),secondDie.end());
		n=firstDie.size();m=secondDie.size();
		int p=n,s=0;
		for (int i=m-1;i>=0;--i){
			while (p&&firstDie[p-1]>secondDie[i]) --p;
			cnt[i+1]=X-secondDie[i]-(n-p)-(m-i-1);
			s+=(n-p);
		}
		for (int i=1;i<m;++i) cnt[i]-=cnt[i+1];
		while (p&&firstDie[p-1]>0) --p;
//		for (int i=1;i<=m;++i) printf("%d ",cnt[i]);puts("");
//		printf("%d\n",s);
		int top=m*p;
		memset(dp,1,sizeof(dp));
		dp[0]=0;
		for (int i=1;i<=m;++i){
			memset(f,1,sizeof(f));
			for (int j=0;j<=top;++j)
				for (int k=0,to,val;k<=cnt[i]&&(to=i*k+j)<=top&&(val=dp[j]+k)<=p;++k)
					f[to]=min(f[to],val);
			memcpy(dp,f,sizeof(f));
//			for (int i=0;i<top;++i) printf("%d ",dp[i]);puts("");
		}
		int res=s;
		for (int i=s;i<=top+s;++i)if (dp[i-s]<=p)
			if (abs(i*2-n*m)<abs(res*2-n*m)) res=i;
		return 1.0*res/n/m;
	}
};

class KingdomAndDice {
public:

static const int MAXN = 52;
static const int LOGN = 8;

double newFairness(std::vector<int> d1, std::vector<int> d2, int num_range) {
    int n = (int)d1.size();

    std::sort(d1.begin(), d1.end());
    std::sort(d2.begin(), d2.end());
    int zero_ct = 0;
    zero_ct = std::distance(d1.begin(), std::upper_bound(d1.begin(), d1.end(), 0));

    std::vector<std::pair<int, int>> contrib;
    int last_d2 = 0, less_d2 = 0;
    d2.push_back(num_range + 1);
    for (int val : d2) {
        int count = std::min<int>(zero_ct,
            val - last_d2 - 1 - std::distance(
                std::upper_bound(d1.begin(), d1.end(), last_d2),
                std::lower_bound(d1.begin(), d1.end(), val)));
        //for (int i = 0; i < count; ++i) contrib.push_back(less_d2);
        if (count > 0) {
            for (int i = 0; i < LOGN; ++i)
                if (count >= (1 << (i + 1)) - 1) contrib.push_back({ less_d2 << i, 1 << i });
                else { contrib.push_back({ less_d2 * (count - (1 << i) + 1), count - (1 << i) + 1 }); break; }
        }
        //printf("%d(%d) %d\n", val, less_d2, count);
        last_d2 = val; ++less_d2;
    }
    //printf("> ");
    //for (int val : contrib) printf(" %d", val); putchar('\n');

    int base = 0;
    for (int val : d1)
        if (val) base += std::distance(d2.begin(), std::lower_bound(d2.begin(), d2.end(), val));

    static bool f[MAXN][MAXN * MAXN];
    std::fill(&f[0][0], &f[0][0] + sizeof f / sizeof f[0][0], false);
    f[0][0] = true;
    for (auto val : contrib) if (val.second != 0) {
        for (int i = zero_ct - val.second; i >= 0; --i)
            for (int j = n * n - val.first; j >= 0; --j)
                if (f[i][j]) f[i + val.second][j + val.first] = true;
    }
    //printf("%d %d\n", base, n * n);

    std::pair<int, int> ans = { n * n + 2, -1 };
    for (int i = 0; i <= zero_ct; ++i)
        for (int j = 0; j <= n * n; ++j) if (f[i][j])
            ans = std::min(ans, std::make_pair(std::abs(2 * (j + base) - n * n), j + base));
    return (double)ans.second / (n * n);
}

};

int main()
{
    KingdomAndDice worker;
    KingdomAndDice_ac judger;
    unsigned int seed = /*1485527783*/(unsigned)time(NULL);
    srand(seed);
    printf("%.4lf\n", worker.newFairness({0, 2, 7, 0}, {6, 3, 8, 10}, 10));
    printf("%.4lf\n", worker.newFairness({0, 0}, {5, 8}, 47));
    printf("%.4lf\n", worker.newFairness({19, 50, 4}, {26, 100, 37}, 1000));
    for (int i = 0; i < 30; ++i) {
        printf("Seed=%u Case=%d ", seed, i);
        std::vector<int> a, b;
        int n = rand() % 50 + 1;
        int rg = 10;
        //for (int i = 0; i < n; ++i) a.push_back(rand() % 2 == 0 ? 0 : rand() % rg + 1);
        //for (int i = 0; i < n; ++i) b.push_back(rand() % rg + 1);
        a.push_back(rand() % rg + 1);
        for (int i = 1; i < 2 * n; ++i) a.push_back(a.back() + rand() % rg + 1);
        for (int i = 0; i < n; ++i) b.push_back(a.back()), a.pop_back();
        std::random_shuffle(a.begin(), a.end());
        std::random_shuffle(b.begin(), b.end());
        int t = rand() % (n + 1); for (int i = 0; i < t; ++i) a[i] = 0;
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        double x = worker.newFairness(a, b, rg * n * 2 + 100000);
        double y = judger.newFairness(a, b, rg * n * 2 + 100000);
        if (fabs(x - y) >= 1e-6) {
            printf("Error! Seed=%u Case=%d  %d\n", seed, i, rg * n * 2);
            for (int t : a) printf(" %d", t); putchar('\n');
            for (int t : b) printf(" %d", t); putchar('\n');
            printf("ja=%.4lf pa=%.4lf\n", y, x);
        }
        printf("ja=%.4lf pa=%.4lf\n", y, x);
    }
    return 0;
}
