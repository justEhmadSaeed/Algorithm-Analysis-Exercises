// Recursive Programming method is used in this program

#include <iostream>
using namespace std;
int CUT_ROD(int *p, int n);
int max(int a, int b);
// Global variable to keep track of the counter
int Count = 0;
int main()
{
    int n, cost[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    cout << "\nEnter the Size of pieces (not more than 10): ";
    cin >> n;
    cout << "\nMaximum Value of " << n << " pieces is $"<<CUT_ROD(cost, n)<<endl;
    cout<<"Function Calls :"<<Count<<" times."<<endl;
}
// Calculates the maximum price of n rod pieces
int CUT_ROD(int *p, int n)
{
    ++Count;
    if (n <= 0)
        return 0;
    int q = 0;
    for (int i = 0; i < n; ++i){
        q = max(q, p[i] + CUT_ROD(p, n - i - 1));
    }
    return q;
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
