template<typename T, T(*op)(T,T)>
struct HLD {
    private:
    int n;
    vector<vector<int>>& to;
    vector<int> size, par, in, head;
    SegmentTree<T, op> tree;
    T e;

    public:
    HLD(vector<vector<int>>& to, const vector<T>& w, T e)
        :to(to), e(e), tree(to.size(), e), n(to.size()) {
        size.resize(n);
        in.resize(n);
        par.resize(n);
        head.resize(n);

        dfs(0, -1);
        int idx = 0;
        decomp(0, -1, idx);
        for(int i = 0;i < n; ++i){
            tree.set(in[i], w[i]);
        }
        tree.build();
    }

    T get(int v) const {
        assert(0 <= v && v < n);
        return tree.get(in[v]);
    }

    void update(int v, T val) {
        assert(0 <= v && v < n);
        tree.update(in[v], val);
    }

    T query(int u, int v) const {
        T retu = e;
        while(head[u] != head[v]){
            if(in[head[u]] < in[head[v]]){
                swap(u, v);
            }

            retu = op(retu, tree.query(in[head[u]], in[u]+1));
            u = par[head[u]];
        }
        if(in[u] > in[v])swap(u, v);
        retu = op(retu, tree.query(in[u], in[v] + 1));
        return retu;
    }

    private:
    void dfs(int v, int p) {
        par[v] = p;
        size[v] = 1;
        if(to[v].size() && to[v][0] == p){
            swap(to[v][0], to[v].back());
        }
        for(int& nxt: to[v]){
            if(nxt == p)continue;
            dfs(nxt, v);
            size[v] += size[nxt];
            if(size[nxt] > size[to[v][0]]){
                swap(nxt, to[v][0]);
            }
        }
    }

    void decomp(int v, int par, int &idx) {
        in[v] = idx;
        ++idx;
        for(int nxt: to[v]){
            if(par == nxt)continue;
            if(to[v][0] == nxt){
                head[nxt] = head[v];
            }else{
                head[nxt] = nxt;
            }
            decomp(nxt, v, idx);
        }
    }
};
