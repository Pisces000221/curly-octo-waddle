#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

class EllysBulls {
public:
const int pow[9] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 1000000000 };

int n, m;
std::vector<int> guesses;
// pair<matches, value>
std::vector<std::pair<std::vector<int>, int>> v1, v2;

inline void generate_all(int offset, int len, std::vector<std::pair<std::vector<int>, int>> &result) {
    result.clear();
    for (int i = 0; i < pow[len]; ++i) {
        std::vector<int> matches; matches.reserve(12);
        for (int j = 0; j < n; ++j) {
            int counter = 0;
            /*if (i == 73) {
                printf("=== %d ===\n", offset);
                for (int k = 0; k < len; ++k) printf("%d %d\n", i / pow[k] % 10, guesses[j] / pow[offset + k] % 10);
            }*/
            for (int k = 0; k < len; ++k)
                if (i / pow[k] % 10 == guesses[j] / pow[offset + k] % 10) ++counter;
            matches.push_back(counter);
        }
        result.push_back({ matches, i });
    }
}

std::string getNumber(std::vector<std::string> guesses_str, std::vector<int> bulls) {
    n = (int)guesses_str.size(), m = (int)guesses_str[0].length();
    guesses.clear();
    for (auto &s : guesses_str) guesses.push_back(strtol(s.c_str(), NULL, 10));

    int p1 = m - m / 2, p2 = m / 2;
    generate_all(0, p1, v1);
    generate_all(p1, p2, v2);

    std::sort(v2.begin(), v2.end());
    bool found = false; int ans = -1;
    std::vector<int> goal(n);
    /*for (auto rhs : v2) {
        printf("RHS %02d (Match", rhs.second);
        for (auto qwq : rhs.first) printf(" %d", qwq); printf(")\n");
    }*/
    for (auto lhs : v1) {
        for (int i = 0; i < n; ++i) goal[i] = bulls[i] - lhs.first[i];
        /*printf("LHS %02d (Match", lhs.second);
        for (auto qwq : lhs.first) printf(" %d", qwq); printf(") (Goal");
        for (auto qwq : goal) printf(" %d", qwq); printf(")\n");*/
        auto lower = std::lower_bound(v2.begin(), v2.end(), std::make_pair(goal, -1)),
            upper = std::upper_bound(v2.begin(), v2.end(), std::make_pair(goal, 0x7fffffff));
        //if (std::distance(lower, upper) > 0)
        //    printf("%d %ld\n", lhs.second, std::distance(lower, upper));
        if (std::distance(lower, upper) > 1) return "Ambiguity";
        else if (std::distance(lower, upper) == 1) {
            if (found) return "Ambiguity";
            else found = true, ans = lhs.second + lower->second * pow[p1];
        }
    }

    char ans_str[24] = { 0 };
    for (int i = 0; i < m; ++i) ans_str[i] = '0' + (ans / pow[m - i - 1]) % 10;
    return found ? ans_str : "Liar";
}

};

int main()
{
    EllysBulls worker;
    puts(worker.getNumber({"1234", "4321", "1111", "2222", "3333", "4444", "5555", "6666", "7777", "8888", "9999"}, {2, 1, 1, 0, 2, 0, 0, 0, 1, 0, 0}).c_str());
    puts(worker.getNumber({"0000", "1111", "2222"}, {2, 2, 2}).c_str());
    puts(worker.getNumber({"666666", "666677", "777777", "999999"}, {2, 3, 1, 0}).c_str());
    puts(worker.getNumber({"000", "987", "654", "321", "100", "010"}, {2, 1, 0, 0, 1, 1}).c_str());
    return 0;
}
