template<typename T>
void warshall_floyd(vector<vector<T>>& cost){
    int n = cost.size();
    for(int k = 0;k < n; ++k){
        for(int i = 0;i < n; ++i){
            for(int j = 0;j < n; ++j){
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }
}