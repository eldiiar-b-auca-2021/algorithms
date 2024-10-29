#include <bits/stdc++.h>
using namespace std;
int m, n;
void connectivity(int i, int j, vector<vector<char>> &v) {
    //v[i][j] = '.';
    if (i < m && v[i][j] == '#') {
        v[i][j] = '.';
        // cout << i << " " << j << endl;
        connectivity(i + 1, j, v);
    }
    if (j < n && v[i][j] == '#') {
        v[i][j] = '.';
        //cout << i << " " << j << endl;
        connectivity(i, j + 1, v);
    }


    if (i - 1 >= 0 && v[i - 1][j] == '#') {
        v[i][j] = '.';
        connectivity(i - 1, j, v);
    }
    if (j - 1 >= 0 && v[i][j - 1] == '#') {
        v[i][j - 1] = '.';
        connectivity(i, j - 1, v);
    }


    if (j + 1 < n && i < m && v[i][j + 1] == '#') {
        v[i][j + 1] = '.';
        connectivity(i, j + 1, v);
    }
    if (j < n && i + 1 < m && v[i + 1][j] == '#') {
        v[i + 1][j] = '.';
        connectivity(i + 1, j, v);
    }


    if (j + 1 < n && i + 1 < m && v[i + 1][j + 1] == '#') {
        v[i + 1][j + 1] = '.';
        connectivity(i + 1, j + 1, v);
    }
    if (j - 1 >= 0 && i - 1 >= 0 && v[i - 1][j - 1] == '#') {
        v[i - 1][j - 1] = '.';
        connectivity(i - 1, j - 1, v);
    }
    if (j - 1 >= 0 && i + 1 < m && v[i + 1][j - 1] == '#') {
        v[i + 1][j - 1] = '.';
        connectivity(i + 1, j - 1, v);
    }


}

int main()
{
    cin >> m;
    cin >> n;
    vector<vector<char>> v(m, vector<char>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char t;
            cin >> t;
            v[i][j] = t;
        }
    }
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++) {
            if (v[i][j] == '#') {
                connectivity(i, j, v);
                count++;
            }
        }
    }
    cout << count<< "\n";

}