// Recursive Dynamic Programming method is used in this program

#include <iostream>
using namespace std;
int MEMOIZED_CUT_ROD(int *p, int n);
int MEMOIZED_CUT_ROD_AUX(int *p, int n, int *r);
int max(int a, int b);
// Global variable to keep track of the counter
int Count = 0;
int main()
{
    int n, cost[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    cout << "Enter the Size of pieces (not more than 10): ";
    cin >> n;
    cout << "Maximum Value of " << n << " pieces is $: " << MEMOIZED_CUT_ROD(cost, n) << endl;
    cout << "Function Calls :" << Count << " times." << endl;
}
int MEMOIZED_CUT_ROD(int *p, int n)
{
    int *r = new int[n + 1];
    for (int i = 0; i <= n; ++i)
        r[i] = -2147483;
    return MEMOIZED_CUT_ROD_AUX(p, n, r);   // Calling Cost calculating function
}
// Calculates the maximum price of n rod pieces
int MEMOIZED_CUT_ROD_AUX(int *p, int n, int *r)
{
    ++Count;
    if (r[n] >= 0)
        return r[n - 1];

    int q = -2147483;
    if (n <= 0)
        q = 0;
    else
    {
        for (int i = 0; i < n; ++i)
        {
            q = max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p, n - i - 1, r));
        }
    }
    r[n - 1] = q;
    return q;
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
