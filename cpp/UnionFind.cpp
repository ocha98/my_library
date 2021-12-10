struct UnionFind{
    vector<int> par;
    UnionFind(int n):par(n, -1){}

    int root(int x){
        if(par[x] < 0)return x;
        return par[x] = root(par[x]);
    }

    int size(int x) {
        return -par[root(x)];
    }

    void conect(int x, int y){
        x = root(x);
        y = root(y);
        if( x == y)return;

        if (par[x] > par[y]) swap(x,y);
        par[x] += par[y];
        par[y] = x;
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }
};


struct UnionFindRanked{
    private:
    vector<int> par;
    vector<int> rank;

    public:
    UnionFindRanked(int n):par(n, -1),rank(n, 0){}

    int root(int x){
        if(par[x] < 0)return x;
        return par[x] = root(par[x]);
    }

    int size(int x) {
        return -par[root(x)];
    }

    void conect(int x, int y){
        //xのほうがランクが高い
        x = root(x);
        y = root(y);
        if( x == y)return;

        //if(rank[x] < rank[y])swap(x, y);
        if(rank[x] == rank[y])rank[x]++;
        par[y] = x;
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }
};