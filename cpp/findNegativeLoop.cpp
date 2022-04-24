struct Edge{
    int from, to, cost;
    Edge(){}
    Edge(int from , int to, int cost):from(from), to(to), cost(cost){}
};

bool find_negative_loop(int V, vector<Edge> es){
    int n = es.size();
    vector<int> dist(V);
    for(int i = 0;i < V; ++i){
        for(int j = 0;j < n; ++j){
            Edge e = es[j];
            if(dist[e.to] > dist[e.from] + e.cost){
                dist[e.to] = dist[e.from] + e.cost;
                if(i == V-1)return true;
            }
        }
    }
    return false;
}