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
        vector<long long> h(n);
        while(f > 0){
            priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> que;
            vector<int> prev_e(n), prev_v(n);
            vector<long long> dist(n, INF);

            dist[s] = 0;
            que.push({0, s});
            while(que.size()){
                long long w = que.top().first;
                int v = que.top().second;
                que.pop();

                if(dist[v] < w)continue;

                int m = es[v].size();
                for(int i = 0;i < m; ++i){
                    Edge& e = es[v][i];
                    if(e.cap <= 0)continue;
                    if(dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prev_v[e.to] = v;
                        prev_e[e.to] = i;
                        que.push({dist[e.to], e.to});
                    }
                }
            }

            if(dist[t] == INF)return -1;

            for(int i = 0;i < n; ++i){
                h[i] += dist[i];
            }

            long long d = f;
            for(int v = t;v != s;v = prev_v[v]){
                d = min(d, es[prev_v[v]][prev_e[v]].cap);
            }

            f -= d;
            resu += d*h[t];
            for(int v = t;v != s;v = prev_v[v]){
                Edge& e = es[prev_v[v]][prev_e[v]];
                e.cap -= d;
                es[v][e.rev].cap += d;
            }
        }
        return resu;
    }
};