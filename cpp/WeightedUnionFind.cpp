template<typename T>
struct WeightedUnionFind{
    vector<int> par;
    vector<T> weight;
    vector<bool> nan;
    WeightedUnionFind(int n):par(n, -1), weight(n,0), nan(n, false){}

    int root(int x){
        if(par[x] < 0){
            return x;
        }
        int r = root(par[x]);
        weight[x] += weight[par[x]];
        return par[x] = r;
    }

    T get_w(int x){
        root(x);
        return weight[x];
    }

    int size(int x) {
        return -par[root(x)];
    }

    T diff(int x, int y){
        return get_w(y) - get_w(x);
    }

    bool is_nan(int x){
        return nan[root(x)];
    }

    void merge(int x, int y, T w){
        //w[y] - w[x] = w

        w += get_w(x);
        w -= get_w(y);

        x = root(x);
        y = root(y);

        if(x == y){
            if(w != 0){
                nan[x] = true;
            }
            return;
        }

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