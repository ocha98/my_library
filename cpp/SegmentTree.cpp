template<typename T>
struct SegmentTree {
    private:
    int n = 1;
    vector<T> node;
    function<T(T,T)> op;
    T e;

    T query(int a, int b, int k, int l, int r) const{
        if(r <= a || b <= l)return e;

        if(a <= l && r <= b)return node[k];

        T vl = query(a, b, 2*k+1, l, (l+r)/2);
        T vr = query(a, b, 2*k+2, (l+r)/2, r);
        return op(vl, vr);
    }

    public:
    SegmentTree(int _n, function<T(T,T)> op, T e):op(op), e(e){
        while(n < _n)n <<= 1;
        node.resize(2*n-1, e);
    }

    SegmentTree(const vector<T>& elem, function<T(T,T)> op, T e):op(op), e(e){
        int _n = elem.size();
        while(n < _n) n <<= 1;
        node.resize(2*n-1, e);
        for(int i = 0;i < _n; ++i){
            node[i+n-1] = elem[i];
        }

        for(int k = n-2; k >= 0; k--) {
            node[k] = op(node[2 * k + 1], node[2 * k + 2]);
        }
    }

    void update(int x, T val){
        assert(x < n);
        x += n-1;

        node[x] = val;
        while(x > 0){
            x = (x-1)/2;
            node[x] = op(node[2*x+1], node[2*x+2]);
        }
    }

    //[a, b)
    T query(int a, int b)const {
        assert(b <= n);
        assert(a <= n);
        return query(a, b, 0, 0, n);
    }

    T get(int i) const{
        assert(i < n);
        i += n-1;
        return node[i];
    }
};
