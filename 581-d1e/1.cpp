#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

class SurveillanceSystem {
public:

static const int MAXN = 52;

std::string getContainerInfo(std::string containers, std::vector<int> reports, int L) {
    int n = containers.length();
    //int m = reports.size();

    std::vector<int> pos[MAXN];
    for (int i = 0; i <= n - L; ++i) {
        int count = 0;
        for (int j = 0; j < L; ++j) count += (containers[i + j] == 'X');
        pos[count].push_back(i);
    }
    int report_count[MAXN] = { 0 };
    for (int r : reports) ++report_count[r];

    bool possib[MAXN][2];
    for (int i = 0; i < n; ++i) possib[i][0] = true, possib[i][1] = false;
    for (int i = 0; i <= L; ++i) if (report_count[i] > 0) {
        for (int p : pos[i])
            for (int j = 0; j < L; ++j) possib[p + j][1] = true;
    }
    for (int i = 0; i <= L; ++i) {
        bool covers[2][MAXN] = {{ false }};
        for (int j = 0; j < report_count[i]; ++j)
            for (int k = 0; k < L; ++k) covers[0][pos[i][j] + k] = true;
        std::reverse(pos[i].begin(), pos[i].end());
        for (int j = 0; j < report_count[i]; ++j)
            for (int k = 0; k < L; ++k) covers[1][pos[i][j] + k] = true;
        if (i == 3) {
            for (int j = 0; j < n; ++j) putchar(covers[0][i] ? 'o' : ' '); putchar('\n');
            for (int j = 0; j < n; ++j) putchar(covers[1][i] ? 'o' : ' '); putchar('\n');
        }
        for (int j = 0; j < n; ++j)
            if (covers[0][j] && covers[1][j]) possib[j][0] = false;
    }

    std::string result(n, '/');
    for (int i = 0; i < n; ++i) switch (((int)possib[i][0] << 1) | possib[i][1]) {
        case 1: result[i] = '+'; break;
        case 2: result[i] = '-'; break;
        case 3: result[i] = '?'; break;
        default: break;
    }
    return result;
}

};

int main()
{
    SurveillanceSystem worker;
    /*puts(worker.getContainerInfo("-X--XX", {1, 2}, 3).c_str());
    puts(worker.getContainerInfo("-XXXXX-", {2}, 3).c_str());
    puts(worker.getContainerInfo("------X-XX-", {3, 0, 2, 0}, 5).c_str());
    puts(worker.getContainerInfo("-XXXXX---X--", {2, 1, 0, 1}, 3).c_str());*/
    puts(worker.getContainerInfo("-XX--X-XX-X-X--X---XX-X---XXXX-----X", {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, 7).c_str());
    return 0;
}
