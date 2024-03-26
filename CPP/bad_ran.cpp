#include <stdio.h>
#include <random>
#include <windows.h>
using namespace std;
#define color(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x % 16)
int main()
{
    random_device r;
    mt19937 g(r());
    uniform_real_distribution<> d(0, 1);
    double m = 0.5, p = 0;
    for (;;)
    {
        p = m;
        if (d(g) >= m)
        {
            m += d(g) / 10.0;
            color(10);
        }
        else
        {
            m -= d(g) / 10.0;
            color(12);
        }
        if (m < 0)
        {
            m = 0;
        }
        printf("%.3llf %+.3llf\n", m, m - p);
        Sleep(100ul);
    }
}