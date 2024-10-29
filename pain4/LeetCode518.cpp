class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int sizeOfCoins = (int)coins.size();
        vector<vector<int>> graph(sizeOfCoins, vector<int>(amount+1,0));
        for (int i = 0; i < sizeOfCoins; i++)
        {
            graph[i][0]=1;
        }
        for (int i = 0; i < sizeOfCoins; i++)
        {
            for (int j = 1; j <= amount; j++)
            {
                int temp = j - coins[i];
                if (temp >= 0)
                {
                    graph[i][j] += graph[i][temp];
                }
                int temp2 = i - 1;
                if (temp2 >= 0 && graph[temp2][j] > 0)
                {
                    graph[i][j] += graph[temp2][j];
                }
            }
        }
        return graph[sizeOfCoins-1][amount];
    }
};