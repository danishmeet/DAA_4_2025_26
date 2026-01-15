#include <bits/stdc++.h>
using namespace std;

long operations = 0;
int maxDepth = 0;

void complexRec(int n, int depth)
{
    maxDepth = max(maxDepth, depth);
    if (n <= 2)
    {
        operations++;
        return;
    }

    int p = n;
    while (p > 0)
    {
        vector<int> temp(n);
        for (int i = 0; i < n; i++)
        {
            temp[i] = i ^ p;
        }
        p >>= 1;
        operations++;
    }

    vector<int> small(n);
    for (int i = 0; i < n; i++)
    {
        small[i] = i * i;
        operations += n;
    }

    if (n % 3 == 0)
    {
        reverse(small.begin(), small.end());
        operations++;
    }
    else
    {
        reverse(small.begin(), small.end());
        operations += n;
    }

    complexRec(n / 2, depth + 1);
    complexRec(n / 2, depth + 1);
    complexRec(n / 2, depth + 1);
}

int main()
{
    int testSize;
    cout << "Enter number of test sizes: ";
    cin >> testSize;

    auto start = chrono::high_resolution_clock::now();
    complexRec(testSize, 1);
    auto end = chrono::high_resolution_clock::now();

    double duration =
        chrono::duration<double, milli>(end - start).count();

    cout << "\n=== Testsize = " << testSize << " ===\n";
    cout << "Operations: " << operations << "\n";
    cout << "Max Recursion Depth: " << maxDepth << "\n";
    cout << "Time Taken: " << duration << " ms\n";

    return 0;
}