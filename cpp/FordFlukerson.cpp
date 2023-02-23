struct FordFlukerson {
    struct Edge {
        int to, rev;
        long long cap;
        Edge(int to, long long cap, int rev):to(to), cap(cap), rev(rev){}
    };
    vector<vector<Edge>> es;
    int n;

    FordFlukerson(int n):n(n), es(n){}

    void add_edge(int from, int to, long long cap){
        es[from].push_back(Edge(to, cap, es[to].size()));
        es[to].push_back(Edge(from, 0, es[from].size()-1));
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while(true){
            vector<bool> used(n);
            long long f = dfs(s, t, INF, used);
            if(f == 0)return flow;
            flow += f;
        }
    }

    private:
    long long dfs(int v, int t, long long f, vector<bool>& used){
        if(v == t)return f;
        used[v] = true;
        for(Edge& e:es[v]){
            if(used[e.to])continue;
            if(e.cap <= 0)continue;

            long long d = dfs(e.to, t, min(f, e.cap), used);
            if(d > 0){
                e.cap -= d;
                es[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }
};