#include <cstdio>
#include <string>
#include <vector>
typedef long long int64;

class CheckerFreeness {
public:

typedef std::pair<int, int> coord;

inline std::vector<int> extract_numbers(const std::vector<std::string> &list) {
    std::vector<int> ret;
    int last = 0;
    for (auto s : list) {
        for (int i = 0; i < s.length(); ++i)
            if (s[i] >= '0' && s[i] <= '9') last = last * 10 + s[i] - '0';
            else ret.push_back(last), last = 0;
    }
    ret.push_back(last);
    return ret;
}

inline int64 cross(const coord &a, const coord &b, const coord &c) {
    return (int64)(b.first - a.first) * (c.second - a.second) -
        (int64)(c.first - a.first) * (b.second - a.second);
}
template <typename T> inline int sign(const T x) { return (x > 0 ? +1 : (x < 0 ? -1 : 0)); }

inline bool check_convex_hull(const std::vector<coord> &p, int i, int j) {
    int prev_sign = -2;
    for (int k = 0; k < (int)p.size(); ++k) if (k != i && k != j) {
        int s = sign(cross(p[i], p[k], p[j]));
        if (prev_sign == -2) prev_sign = s;
        else if (prev_sign != s) return false;
    }
    return true;
}

inline bool check_quad(const coord &a1, const coord &a2, const coord &b1, const coord &b2) {
    return
        sign(cross(a1, b1, a2)) * sign(cross(a1, b2, a2)) < 0 &&
        sign(cross(b1, a1, b2)) * sign(cross(b1, a2, b2)) < 0;
}

std::string isFree(
    std::vector<std::string> whiteX,
    std::vector<std::string> whiteY,
    std::vector<std::string> blackX,
    std::vector<std::string> blackY)
{
    std::vector<coord> whites, blacks;
    std::vector<int> qwq[4];
    qwq[0] = extract_numbers(whiteX);
    qwq[1] = extract_numbers(whiteY);
    qwq[2] = extract_numbers(blackX);
    qwq[3] = extract_numbers(blackY);
    int n_wh = (int)qwq[0].size(), n_bl = (int)qwq[2].size();
    for (int i = 0; i < n_wh; ++i) whites.push_back({qwq[0][i], qwq[1][i]});
    for (int i = 0; i < n_bl; ++i) blacks.push_back({qwq[2][i], qwq[3][i]});

    for (int i = 0; i < n_bl; ++i)
        for (int j = 0; j < n_bl; ++j) if (i != j && check_convex_hull(blacks, i, j)) {
            // The inner loops will be executed O(n) times since # of segments on CH is O(n)
            for (int p = 0; p < n_wh; ++p)
                for (int q = p + 1; q < n_wh; ++q)
                    if (check_quad(blacks[i], blacks[j], whites[p], whites[q])) return "NO";
        }
    for (int i = 0; i < n_wh; ++i)
        for (int j = 0; j < n_wh; ++j) if (i != j && check_convex_hull(whites, i, j)) {
            for (int p = 0; p < n_bl; ++p)
                for (int q = p + 1; q < n_bl; ++q)
                    if (check_quad(whites[i], whites[j], blacks[p], blacks[q])) return "NO";
        }
    return "YES";
}

};

int main()
{
    CheckerFreeness worker;
    puts(worker.isFree({"2", "5", "3", " ", "1", "7", "3"}, {"180 254"}, {"32", "5 1", "42"}, {"462 423"}).c_str());
    puts(worker.isFree({"1 10000000 9999999"}, {"1 9999999 1"}, {"2 5000000 9999998"}, {"2 5000001 9999999"}).c_str());
    puts(worker.isFree({"6115 9723 3794 2275 2268 2702 3657 915 7953 2743 7" ,"716 9645 2547 9490 9365 326 6601 5215 6771 7153 72" ,"93 5922 714 2258 4369 9524 302 8417 6620 1143"}, {"621 1611 7140 503 5345 7202 681 4908 2510 5908 279" ,"6 6286 6873 6682 9197 6710 8517 1913 7784 8533 665" ,"4 446 3561 7241 6168 2025 4739 9501 5340 6446"}, {"6833 131 4151 1776 1959 7210 1903 6107 598 6220 94" ,"24 5374 6718 2919 6068 6644 5070 710 7121 1630 370" ,"3 1051 5739 9294 8798 3371 8107 2130 6608 534"}, {"7496 2412 2801 3473 5810 2714 7853 9714 5470 3558 " ,"8143 2391 8234 7292 9311 1636 8978 1107 2262 9175 " ,"7259 8842 5294 7209 2317 3825 3413 820 3774 5393"}).c_str());
    return 0;
}
