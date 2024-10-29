#include <bits/stdc++.h>
using namespace std;
void dfs(string s, vector<vector<string>> &m, map<string, bool> &vis){
    vis[s] = true;
    for (auto it : m)
    {
        for (auto it2 : it)
            if (!it2.empty() && !vis[it2])
                dfs(it2, m, vis);
    }
}
int main()
{
    int n;
    cin >> n;
    vector<vector<string>> v(n);
    map<string, set<string>> m;
    map<string, bool> visited;
    for (int i = 0; i < n; i++)
    {
        string f;
        string s;
        cin >> f;
        cin >> s;
        v.push_back({f,s});
        visited[f] = false;
    }
    for (auto it : m)
    {
        cout << it.first << " ";
        for (auto it2 : it.second)
        {
            cout << it2 << " ";
        }
        cout << "\n";

    }
    for (string s; cin >> s;)
    {
        int count = 0;
        dfs(s, v,  visited);
        for (auto it : visited)
            if (it.second) count++;
        if (count > 1)
        {
            cout << s << " safe\n";
        }else
        {
            cout << s << " unsafe\n";
        }
        for (auto it : visited)
        {
            it.second = false;
        }
    }


}