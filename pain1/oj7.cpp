#include <bits/stdc++.h>

using namespace std;
void dfs(vector<vector<int>> &v, int manually, vector<bool> &visited)
{
    visited[manually] = true;
    for (auto it : v[manually])
    {
        if (!visited[it])
            dfs(v, it, visited);
    }
    return;
}
int main()
{
    int c;
    cin >> c;
    while(c--)
    {
        int n,m,l;
        cin >> n >> m >> l;
        vector<vector<int>> v(n);
        while(m--)
        {
            int a, b;
            cin >> a >> b;
            v[--a].push_back(--b);
        }
        vector<bool> visited(n, false);
        while(l--)
        {
            int z;
            cin >> z;
            dfs(v, z-1, visited);
        }
        int count = 0;
        for (auto it : visited)
        {
            if (it)
            {
                count++;
            }

        }
        cout << count << endl;
    }
}
