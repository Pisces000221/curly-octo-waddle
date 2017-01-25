#include <cstdio>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

class EllysRoomAssignmentsDiv1 {
public:

double getAverage(std::vector<std::string> ratings_str) {
    double ans = 0.0;
    std::vector<int> ratings;
    std::string s;
    for (std::string &t : ratings_str) s.append(t);
    if (s[s.length() - 1] != ' ') s.push_back(' ');
    for (int p = 0; p < s.length(); ++p) {
        int val = 0;
        while (s[p] >= '0' && s[p] <= '9') val = val * 10 + s[p++] - '0';
        ratings.push_back(val);
    }

    int n = (int)ratings.size();
    int r = (n % 20 == 0 ? n / 20 : n / 20 + 1);
    printf("Rooms = %d\n", r);
    int elly = ratings[0], elly_idx;
    std::sort(ratings.begin(), ratings.end(), std::greater<int>());
    for (int i = 0; i < n; ++i) if (ratings[i] == elly) { elly_idx = i; break; }

    for (int i = 0; i + r <= n; i += r) {
        double cur_group = 0.0;
        if (elly_idx >= i && elly_idx < i + r) {
            cur_group = elly;
        } else {
            for (int j = 0; j < r; ++j) cur_group += ratings[i + j];
            cur_group /= r;
        }
        printf("Group #%d (%d-%d): %.3lf\n", i + 1, i * r + 1, i * r + r, cur_group);
        ans += cur_group;
    }
    if (n % r != 0) {
        if (elly_idx / r >= n / r) {
            ans = (ans + elly) / (n / r + 1);
        } else {
            double appended_prob = (double)(n % r) / r;
            double appended_avg = 0.0;
            for (int i = n - n % r; i < n; ++i) appended_avg += ratings[i];
            appended_avg /= (n % r);
            ans = appended_prob * (ans + appended_avg) / (n / r + 1) + (1.0 - appended_prob) * ans / (n / r);
        }
    } else ans /= (n / r);

    return ans;
}

};

int main()
{
    EllysRoomAssignmentsDiv1 worker;
    //printf("%.4lf\n", worker.getAverage({"1924 1242 1213 1217 2399 1777 2201 2301 1683 2045 ", "1396 2363 1560 2185 1496 2244 2117 2207 2098 1319 ", "2216 1223 1256 2359 2394 1572 2151 2191 2147 2253 ", "1633 2217 2211 1591 1310 1209 1430 1445 1988 2030 ", "1947 1202 1203"}));
    //printf("%.4lf\n", worker.getAverage({"3380 3413 3254 3515 2885 2946 2790 3140"}));
    printf("%.4lf\n", worker.getAverage({"2367 1395 1639 1842 1426 2393 2348 1571 2077 12", "2", "2 1966 1495 13", "09 1251 3039 1566 1989 2083 1819 1875 ", "1579 2206 1503 1461 2262 2116 1429 2150 1834 2097 ", "2093 1518 1923 1796 1669 2342 1826 2374 1635 1683 ", "1656 2190 1632 1946 1207 1293 2029 2243 2252 1559 ", "2366 1590 1563 2319 1391 1255 1727 1565 1911 1679 ", "1282 2358 1682 2148 3555 2362 1208 2044 1949 1980 ", "1983 2215 2184 1545 1665 2146 1272 2110 1889 1829 ", "1808 2065 1987 1297 2216 1609 1318 1816 1444 20", "00 1404"}));
    return 0;
}
