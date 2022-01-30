struct Edge{
    int to, cost;
    Edge(){}
    Edge(int to, int cost):to(to), cost(cost){}
};

vector<int> dijkstra(int start, vector<vector<Edge>>& es){
    int n = es.size();
    vector<int> dist(n, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> que;
    dist[start] = 0;
    que.push(pair<int,int>(0, start));
    while(!que.empty()){
        int w = que.top().first;
        int v = que.top().second;
        que.pop();

        if(dist[v] < w)continue;

        int m = es[v].size();
        for(int i = 0;i < m; ++i){
            Edge e = es[v][i];
            if(dist[e.to] > dist[v] + e.cost){
                dist[e.to] = dist[v] + e.cost;
                que.push(pair<int,int>(dist[e.to], e.to));
            }
        }
    }
    return dist;
}