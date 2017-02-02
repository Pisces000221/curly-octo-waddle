#include <cstdio>
#include <algorithm>
#include <vector>

class TheJediTest {
public:

int minimumSupervisors(std::vector<int> students, int K) {
    int n = (int)students.size();
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        ans += students[i] / K;
        students[i] %= K;
        if (students[i] > 0) {
            if (i + 1 < n) {
                int moves = std::min(students[i + 1], K - students[i]);
                students[i + 1] -= moves; students[i] += moves;
            }
            if (i + 2 < n) {
                int moves = std::min(students[i + 2], K - students[i]);
                students[i + 2] -= moves; students[i] += moves;
            }
            ++ans;
        }
    }
    return ans;
}

};

int main()
{
    TheJediTest worker;
    printf("%d\n", worker.minimumSupervisors({3, 6, 3}, 4));
    printf("%d\n", worker.minimumSupervisors({1, 1, 1, 1}, 4));
    printf("%d\n", worker.minimumSupervisors({0, 0, 0, 0}, 12345));
    printf("%d\n", worker.minimumSupervisors({15, 0, 13, 4, 29, 6, 2}, 7));
    printf("%d\n", worker.minimumSupervisors({1284912, 1009228, 9289247, 2157, 2518, 52781, 2, 2818, 68}, 114));
    return 0;
}
