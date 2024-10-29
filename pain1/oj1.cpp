#include <bits/stdc++.h>
using namespace std;

void dfs(int start, vector<bool> &vi, vector<vector<int>> &adj, int p){
    vi[start] = true;
    for (int j=0; j<p; j++){
        if(adj[start][j] && !vi[j])
            dfs(j,vi,adj,p);
    }
}
int main()
{
    for (int p,c; cin>>p>> c && p != 0 && c != 0;)
    {
        vector<vector<int>> adj(p, vector<int>(p,0));
        vector<pair<int,int>> pairs;
        for (int i = 0; i < c; i++)
        {
            int u,v;
            cin >> u;
            cin >> v;
            adj[u][v] = 1;
            adj[v][u] = 1;
            pairs.emplace_back(u,v);
        }
        bool no = true;
        for(auto e: pairs) {
            adj[e.first][e.second] = 0;
            adj[e.second][e.first] = 0;
            vector<bool> visited(p,false);
            dfs(0,visited,adj,p);
            bool in = false;
            for(int i=0; i<p; i++) {
                if(!visited[i]) {
                    in = true;
                    no = false;
                    cout << "Yes\n";
                    break;
                }
            }
            if(in)
                break;
            adj[e.first][e.second] = 1;
            adj[e.second][e.first] = 1;
        }
        if (no)
        {
            cout << "No\n";
        }



    
    }

}
