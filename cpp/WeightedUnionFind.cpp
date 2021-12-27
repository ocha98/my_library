struct WeightedUnionFind{
    vector<int> par;
    vector<int> weight;
    UnionFind(int n):par(n, -1), w(n,0){}

    int root(int x){
        if(par[x] < 0){
            return x;
        }
        weight[x] += weight[par[x]];
        return par[x] = root(par[x]);
    }

    int size(int x) {
        return -par[root(x)];
    }

    void merge(int x, int y, int w){
        //w[y] - w[x] = w
        w += weight[x];
        w -= weight[y];

        x = root(x);
        y = root(y);

        if(par[x] > par[y]){
            swap(x, y);
            w = -w;
        }
        par[x] += par[y];
        par[y] = x;
        weight[y] = w;
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }
};
