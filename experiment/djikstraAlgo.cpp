#include <bits/stdc++.h>
using namespace std;

vector<bool> visited(7, false);
vector<long> shortDis(7, INT_MAX);

int nearestNeighbor() {
    long nearest = INT_MAX;
    int ind = 0;
    for (int i = 0; i < 7; i++) {
        if (!visited[i] && shortDis[i] < nearest) {
            nearest = shortDis[i];
            ind = i;
        }
    }
    return ind;
}

void dijkstra(vector<vector<int>> &graph, int src) {
    shortDis[src] = 0;
    for (int count = 0; count < 7; count++) {
        int nearest = nearestNeighbor();
        visited[nearest] = true;
        for (int i = 0; i < 7; i++) {
            if (!visited[i] && graph[nearest][i] != INT_MAX &&
                shortDis[nearest] != INT_MAX &&
                (shortDis[nearest] + graph[nearest][i] < shortDis[i])) {
                shortDis[i] = shortDis[nearest] + graph[nearest][i];
            }
        }
    }
}

int main() {
    vector<vector<int>> arr(7, vector<int>(7, INT_MAX));
    for (int i = 0; i < 9; i++) {
        int t1, t2, v;
        cin >> t1 >> t2 >> v;
        arr[t1 - 1][t2 - 1] = v;
        arr[t2 - 1][t1 - 1] = v;
    }

    // Output the adjacency matrix
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // Initialize shortDis vector to infinity
    fill(shortDis.begin(), shortDis.end(), INT_MAX);

    dijkstra(arr, 0);

    // Output the shortest distances from the source (0) to all other vertices
    for (auto distance : shortDis) {
        cout << distance << endl;
    }

    return 0;
}
