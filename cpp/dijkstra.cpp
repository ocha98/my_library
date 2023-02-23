struct Edge{
    int to;
    long long cost;
    Edge(){}
    Edge(int to, long long cost):to(to), cost(cost){}
};

vector<long long> dijkstra(int start, const  vector<vector<Edge>>& es){
    int n = es.size();
    vector<long long> dist(n, INF);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> que;
    dist[start] = 0;
    que.push({0, start});
    while(!que.empty()){
        long long w = que.top().first;
        int v = que.top().second;
        que.pop();

        if(dist[v] < w)continue;

        int m = es[v].size();
        for(int i = 0;i < m; ++i){
            const Edge& e = es[v][i];
            if(dist[e.to] > dist[v] + e.cost){
                dist[e.to] = dist[v] + e.cost;
                que.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}