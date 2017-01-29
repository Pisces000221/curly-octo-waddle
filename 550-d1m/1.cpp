#include <cstdio>
#include <string>
#include <vector>
typedef long long int64;

class CheckerExpansion {
public:

static char get_grid_status(int64 turns, int64 x, int64 y) {
    if ((x + y) % 2 != 0 || y > x || (x + y) / 2 > turns - 1) return '.';
    int64 row = (x + y) / 2, col = (x - y) / 2;
    bool is_alice = (row % 2 == 0);
    // Whether binom(row, col) is odd
    bool binom_parity = ((row & col) == col);
    return binom_parity ? (is_alice ? 'A' : 'B') : '.';
}

std::vector<std::string> resultAfter(int64 t, int64 x0, int64 y0, int w, int h) {
    std::vector<std::string> ret;
    for (int64 y = y0 + h - 1; y >= y0; --y) {
        std::string s = "";
        for (int64 x = x0; x < x0 + w; ++x) s += get_grid_status(t, x, y);
        ret.push_back(s);
    }
    return ret;
}

};

int main()
{
    CheckerExpansion worker;
    for (auto s : worker.resultAfter(1, 0, 0, 4, 4)) puts(s.c_str());
    for (auto s : worker.resultAfter(5, 4, 1, 3, 4)) puts(s.c_str());
    for (auto s : worker.resultAfter(1024, 1525, 512, 20, 2)) puts(s.c_str());
    for (auto s : worker.resultAfter(53, 85, 6, 5, 14)) puts(s.c_str());
    return 0;
}
