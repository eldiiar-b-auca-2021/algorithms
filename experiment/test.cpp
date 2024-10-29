#include "bits/stdc++.h"

using namespace std;
vector<int> shortDis(7, INFINITY);
vector<bool> visited(7, false);
vector<int> previous(10);
int findNearestNeighbour()
{
    int min = INFINITY;
    int index = 0;
    for (int i = 0; i < 7; i++)
    {
        if (!visited[i] && min>shortDis[i])
        {
            min = shortDis[i];
            index = i;
        }
    }
    return index;
}
void dijkstra(vector<vector<int>> &v, int src)
{
    shortDis[src] = 0;
    for (int i = 0; i < v.size(); i++)
    {
        int indexOfNearest = findNearestNeighbour();
        visited[indexOfNearest] = true;
        for (int j = 0; j < v.size(); j++)
        {
            if (!visited[j] && v[indexOfNearest][j] != INT_MAX &&
                shortDis[indexOfNearest] != INT_MAX &&
                (shortDis[indexOfNearest] + v[indexOfNearest][j] < shortDis[j])){
                shortDis[j] = v[indexOfNearest][j] + shortDis[indexOfNearest];
                previous[j] = indexOfNearest;
            }
        }

    }
}
int main()
{
    map<int, int> m;
    m[0] = 1;

    cout << m[0] << " " << m[1] << endl;
//    vector<vector<int>> arr(7, vector<int>(7, INT_MAX));
//    for (int i = 0; i < 9; i++) {
//        int t1, t2, v;
//        cin >> t1 >> t2 >> v;
//        arr[t1 - 1][t2 - 1] = v;
//      //  arr[t2 - 1][t1 - 1] = v;
//    }
//
//    // Output the adjacency matrix
//    for (int i = 0; i < 7; i++) {
//        for (int j = 0; j < 7; j++) {
//            cout << arr[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    // Initialize shortDis vector to infinity
//
//    dijkstra(arr, 0);
//    for (auto it : shortDis)
//    {
//        cout << it << endl;
//    }
//    for (int i = 0; i < 10; i++)
//    {
//        cout << i << " " << previous[i] << endl;
//    }
}