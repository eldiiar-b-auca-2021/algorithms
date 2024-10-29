#include "bits/stdc++.h"

using namespace std;
void dfs(int pos, int &value, vector<vector<int>> &adj, vector<int> &v, vector<bool> &completed){
    completed[pos] = true;
    //cout << value << endl;
    for (auto it : adj[pos])
    {
        if (!completed[it]){
            value += v[it];
            dfs(it, value, adj, v, completed);
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
//    for (auto it : adj) {
//        for (auto it2: it) {
//            cout << it2 << " ";
//        }
//        cout << "\n";
//    }
    vector<bool> completed(n, false);
    bool result = true;
    for (int i = 0; i < n; i++)
    {
        if (!completed[i]) {
            int temp = v[i];
            dfs(i, temp, adj, v, completed);
            if (temp != 0) {
                cout << "IMPOSSIBLE" << "\n";
                result = false;
                break;
            }
        }
    }
    if (result)
        cout << "POSSIBLE" << "\n";
}