#include <cstdio>
#include <algorithm>

class TheBrickTowerEasyDivOne {
public:

int find(int redCount, int redHeight, int blueCount, int blueHeight) {
    if (redHeight == blueHeight) {
        return std::min(redCount, blueCount) * 2 + (redCount == blueCount ? 0 : 1);
    } else {
        return std::min(redCount, blueCount) * 3 + (redCount == blueCount ? 0 : 1);
    }
}

};

int main()
{
    TheBrickTowerEasyDivOne worker;
    printf("%d\n", worker.find(1, 2, 3, 4));
    printf("%d\n", worker.find(4, 4, 4, 7));
    printf("%d\n", worker.find(7, 7, 4, 4));
    printf("%d\n", worker.find(47, 47, 47, 47));
    return 0;
}
