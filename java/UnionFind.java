class UnionFind{
    private int[] par;
    UnionFind(int n){
        par = new int[n];
        Arrays.fill(par, -1);
    }

    int root(int x){
        if(par[x] < 0)return x;
        return par[x]  = root(par[x]);
    }

    int size(int x){
        return -par[root(x)];
    }

    void unite(int x, int y){
        x = root(x);
        y = root(y);
        if(x == y)return;

        if(par[x] > par[y]){
            // swap
            int tmp = x;
            x = y;
            y = tmp;
        }

        par[x] += par[y];
        par[y] = x;
    }

    boolean same(int x, int y){
        return root(x) == root(y);
    }
}