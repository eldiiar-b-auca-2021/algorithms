#include <bits/stdc++.h>
using namespace std;
void dfs(vector<vector<int>> &adj, int start, int &count, vector<bool> &vis)
{
    vis[start] = true;
    for (int i = 0; i < adj[start].size(); i++)
    {
        if (!vis[i] && adj[start][i])
        {
            dfs(adj, i,count, vis);
        }
    }
}

int main()
{
    int tc;
    cin >> tc;
    while(tc--)
    {
        int nv;
        cin >> nv;
        vector<vector<int>> adj(nv, vector<int>(nv,0));
        int r;
        cin >> r;
        while(r--)
        {
            int a, b;
            cin >> a;
            cin >> b;
            adj[a][b] = 1;
            adj[b][a] = 1;
        }
        int count = 0;
        vector<bool> vis(nv,false);
        for (int j = 0; j < vis.size(); j++) {
            if (!vis[j]) {
                count++;
                dfs(adj, j, count, vis);
            }
        }

        cout << count-1 <<"\n";
    }
}