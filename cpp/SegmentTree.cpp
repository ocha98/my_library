template<typename T,  T(*op)(T, T)>
struct SegmentTree {
    // 1-index tree
    private:
    int n = 1;
    vector<T> node;
    T e;

    public:
    SegmentTree(int _n, T e): e(e){
        while(n < _n)n <<= 1;
        node.resize(2*n, e);
    }

    SegmentTree(const vector<T>& elem, T e):e(e){
        int _n = elem.size();
        while(n < _n) n <<= 1;
        node.resize(2*n, e);

        for(int i = 0;i < _n; ++i){
            set(i, elem[i]);
        }
        build();
    }

    void set(int i, T val) {
        assert(i < n);
        node[i + n] = val;
    }

    void build() {
        for(int k = n-1; k > 0; --k) {
            node[k] = op(node[k<<1], node[k << 1 | 1]);
        }
    }

    void update(int x, T val){
        assert(x < n);
        x += n;

        node[x] = val;
        while(x > 1){
            x >>= 1;
            node[x] = op(node[x<<1], node[x<<1 | 1]);
        }
    }

    //[l, r)
    T query(int l, int r)const {
        assert(l <= n);
        assert(l <= n);
        l += n;
        r += n;
        T x = e;
        while(l < r){
            if(l&1){
                x = op(x, node[l]);
                ++l;
            }
            if(r&1){
                --r;
                x = op(x, node[r]);
            }
            l >>= 1;
            r >>= 1;
        }

        return x;
    }

    T get(int i) const{
        assert(i < n);
        i += n;
        return node[i];
    }
};
