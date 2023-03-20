struct LCA {
    vector<vector<int>> to, parent;
    vector<int> dist;
    const int n;
    int k = 1;

    LCA(vector<vector<int>>& to):n(to.size()), dist(to.size()), to(to){
        while((1<<k) < n)k++;
        parent.assign(k, vector<int>(n, -1));
        dfs(0, -1, 0);
        for(int i = 0;i < k-1; ++i){
            for(int v = 0;v < n; ++v){
                if(parent[i][v] < 0){
                    parent[i+1][v] = -1;
                }else{
                    parent[i+1][v] = parent[i][parent[i][v]];
                }
            }
        }
    }

    int get_lca(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        if(dist[u] < dist[v])swap(u, v);
        for(int i = 0;i < k; ++i){
            int diff = dist[u] - dist[v];
            if(diff >> i & 1){
                u = parent[i][u];
            }
        }

        if(u == v)return u;

        for(int i = k-1;i >= 0; --i){
            if(parent[i][u] != parent[i][v]){
                u = parent[i][u];
                v = parent[i][v];
            }
        }

        return parent[0][u];
    }

    int get_dist(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        int p = get_lca(u, v);
        return dist[u] + dist[v] - 2*dist[p];
    }

    private:
    void dfs(int v, int p, int d){
        parent[0][v] = p;
        dist[v] = d;
        for(int nxt: to[v]){
            if(nxt == p)continue;
            dfs(nxt, v, d+1);
        }
    }
};