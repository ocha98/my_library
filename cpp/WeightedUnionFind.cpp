struct WeightedUnionFind{
    vector<int> par;
    vector<int> weight;
    WeightedUnionFind(int n):par(n, -1), weight(n,0){}

    int root(int x){
        if(par[x] < 0){
            return x;
        }
        int r = root(par[x]);
        weight[x] += weight[par[x]];
        return par[x] = r;
    }

    int get_w(int x){
        root(x);
        return weight[x];
    }

    int size(int x) {
        return -par[root(x)];
    }

    int diff(int x, int y){
        return get_w(y) - get_w(x);
    }

    void merge(int x, int y, int w){
        //w[y] - w[x] = w

        w += get_w(x);
        w -= get_w(y);

        x = root(x);
        y = root(y);

        if(x == y)return;

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