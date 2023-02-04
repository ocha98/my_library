struct MinCostFlow {
    struct Edge {
        int to, rev;
        long long cap, cost;
        Edge(int to, long long cap, long long cost, int rev):to(to),rev(rev),cap(cap),cost(cost){}
    };
    int n;
    vector<vector<Edge>> es;

    MinCostFlow(int n):n(n), es(n){}

    void add_edge(int from, int to, long long cap, long long cost){
        es[from].emplace_back(Edge(to, cap, cost, es[to].size()));
        es[to].emplace_back(Edge(from, 0, -cost, es[from].size()-1));
    }

    long long min_cost_flow(int s, int t, long long f){
        long long resu = 0;
        while(f > 0){
            vector<int> prev_e(n), prev_v(n);
            vector<long long> dist(n, INF);
            dist[s] = 0;
            bool update = true;
            while(update) {
                update = false;
                for(int i = 0;i < n; ++i){
                    if(dist[i] == INF)continue;
                    int m = es[i].size();
                    for(int j = 0;j < m; ++j){
                        Edge& e = es[i][j];
                        if(e.cap <= 0)continue;
                        if(dist[e.to] > dist[i] + e.cost){
                            dist[e.to] = dist[i] + e.cost;
                            prev_v[e.to] = i;
                            prev_e[e.to] = j;
                            update = true;
                        }
                    }
                }
            }

            if(dist[t] == INF)return -1;

            long long d = f;
            for(int v = t;v != s;v = prev_v[v]){
                d = min(d, es[prev_v[v]][prev_e[v]].cap);
            }

            f -= d;
            resu += d*dist[t];
            for(int v = t;v != s;v = prev_v[v]){
                Edge& e = es[prev_v[v]][prev_e[v]];
                e.cap -= d;
                es[v][e.rev].cap += d;
            }
        }
        return resu;
    }
};