#include "bits/stdc++.h"

using namespace std;

int main()
{

    vector<int> k(40);
    k[0] = 0;
    k[1] = 1;
    for (int i = 2; i < k.size(); i++)
    {
        k[i] = k[i-1] + k[i-2];
    }
    for (auto it : k)
    {
        cout << it << " ";
    }
}