#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

class RepeatNumberCompare {
public:

static const int MAXLEN = 602;

std::string compare(int x1, int k1, int x2, int k2) {
    char x1_str[15], x2_str[15];
    int s[MAXLEN] = { 0 }, t[MAXLEN] = { 0 };

    sprintf(x1_str, "%d", x1);
    sprintf(x2_str, "%d", x2);
    int x1_len = strlen(x1_str), x2_len = strlen(x2_str);
    for (int i = 0; i < x1_len * k1; ++i) s[i] = x1_str[x1_len - 1 - i % x1_len];
    for (int i = 0; i < x2_len * k2; ++i) t[i] = x2_str[x2_len - 1 - i % x2_len];

    //for (int i = 0; i < x1_len * k1; ++i) putchar(s[i]); putchar('\n');
    //for (int i = 0; i < x2_len * k2; ++i) putchar(t[i]); putchar('\n');
    for (int i = MAXLEN - 1; i >= 0; --i)
        if (s[i] != t[i]) return (s[i] < t[i] ? "Less" : "Greater");
    return "Equal";
}

};

int main()
{
    RepeatNumberCompare worker;
    puts(worker.compare(1234, 3, 70, 4).c_str());
    puts(worker.compare(1010, 3, 101010, 2).c_str());
    return 0;
}
