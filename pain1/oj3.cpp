#include <bits/stdc++.h>
using namespace std;
void dfs(int start, vector<bool> &vis, vector<vector<int>> &adj){
    vis[start] = true;
    for (auto it : adj[start])
    {
        if (!vis[it]){
            dfs(it, vis, adj);
        }
    }
}
int main()
{
    int n,m;
    cin >> n;
    cin >> m;
    vector<vector<int>> adj(n);
    while(m--)
    {
        int a,b;
        cin >> a ;
        cin >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<bool> vis(n, false);
    dfs(0, vis, adj);
    bool connected = true;
    for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                cout << i+1 <<"\n";
                connected = false;
            }
        }
    if (connected)
        cout << "Connected\n";





}