void warshall_floyd(vector<vector<int>>& cost){
    int n = cost.size();
    for(int i = 0;i < n; ++i){
        for(int j = 0;j < n; ++j){
            for(int k = 0;k < n; ++k){
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }
}