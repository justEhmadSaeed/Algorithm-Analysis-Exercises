// Bottom Up dynamic programming method is used in this program

#include <iostream>
using namespace std;
int BOTTOM_UP_CUT_ROD(int *p, int n);
int max(int a, int b);
// Global variable to keep track of the counter
int Count = 0;
int main()
{
    int n, cost[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    cout << "Enter the Size of pieces (not more than 10): ";
    cin >> n;
    cout << "Maximum Value of " << n << " pieces is $" << BOTTOM_UP_CUT_ROD(cost, n) << endl;
    cout << "Function Calls :" << Count << " times." << endl;
}
// Calculates the maximum price of n rod pieces
int BOTTOM_UP_CUT_ROD(int *p, int n)
{
    Count++;
    int *r = new int[n + 1];
    r[0] = 0;
    int q = -2147483;
    for (int j = 1; j <= n; ++j)
    {
        q = -2147483;
        for (int i = 0; i < j; ++i)
        {
            ++Count;
            q = max(q, p[i] + r[j - i - 1]);
        }
        r[j] = q;
    }

    return r[n];
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
