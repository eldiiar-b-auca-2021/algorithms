#include "bits/stdc++.h"
using namespace std;

void dfs(vector<vector<char>> &v, int i, int j, int h, int w){
    if (v[i][j] == 'G')
    {
        v[i][j] == '.';
    }
    if (v[i][j] == '#')
    {
        return;
    }
    if (i + 1 < h && v[i+1][j] == 'T' ||
        j + 1 < w && v[i][j+1] == 'T' ||
        j > 0 && v[i][j-1] == 'T' ||
        i > 0 && v[i-1][j] == 'T'
        ){
        return;
    }



    dfs(v, i+1, j, h, w);
    dfs(v, i-1, j, h, w);
    dfs(v, i, j+1, h, w);
    dfs(v, i, j-1, h, w);
}
int main()
{
    int w, h;
    cin >> w;
    cin >> h;
    vector<vector<char>> v(h, vector<char>(w));
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            char t;
            cin >> t;
            v[i][j] = t;
        }
    }
    bool isFinished = false;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (v[i][j] == 'P')
            {
                dfs(v, i,j, h, w);
                isFinished = true;
                break;
            }

        }
        if (isFinished)
            break;
        cout << "\n";
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
           cout << v[i][j] << " ";

        }
        cout << "\n";
    }

}
