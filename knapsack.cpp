#include <bits/stdc++.h>
using namespace std;
vector<int> selected;

int knapsack(int W, int wt[], int val[], int n)
{
    int B[n + 1][W + 1]; // Create a 2D array to store the values
    for (int w = 0; w <= W; w++)
    {
        B[0][w] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        B[i][0] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (wt[i-1] <= w)
            {
                B[i][w] = max(val[i-1] + B[i - 1][w - wt[i-1]], B[i - 1][w]);
            }
            else
            {
                B[i][w] = B[i - 1][w];
            }
        }
    }
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) { // start from the last item 
        if (B[i][w] != B[i - 1][w]) {
            selected.push_back(i - 1); 
            w -= wt[i - 1];
        }
    }
    return B[n][W];
}

int main()
{
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    int wt[n], val[n];
    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; i++)
    {
        cin >> wt[i];
    }
    cout << "Enter the values of the items: ";
    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
    }
    cout << "Enter the maximum weight capacity of the knapsack: ";
    cin >> W;
    cout << "The maximum value that can be obtained is: " << knapsack(W, wt, val, n) << endl;

    cout << "The items selected are: ";
    for (int i = 0; i < selected.size(); i++) {
        cout << selected[i] + 1 << " "; // Display item indices (1-based)
    }
    cout << endl;
    return 0;
}