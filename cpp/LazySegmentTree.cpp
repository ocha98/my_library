template<typename T, typename U = T>
struct LazySegmentTree {
    int n = 1;
    vector<T> node;
    vector<U> lazy;
    T eT; // Tの単位元
    U eU; // Uの単位元

    function<T(T,T)> op;// T*T -> T を定義する関数
    function<U(U,U)> propa;// 伝搬関数 U*U -> U を定義
    function<T(T, U)> merge;// U -> T と変換する関数

    LazySegmentTree(int _n, T eT, U eU, function<T(T,T)> op, function<U(U,U)> propa, function<T(T, U)> merge)
                :eT(eT), eU(eU), op(op), propa(propa), merge(merge){
        while(n < _n)n <<= 1;

        node.resize(2*n-1, eT);
        lazy.resize(2*n-1, eU);
    }

    void eval(int k){
        if(lazy[k] == eU)return;

        node[k] = merge(node[k], lazy[k]);

        if(k < n-1){
            lazy[2*k+1] = propa(lazy[2*k+1], lazy[k]);
            lazy[2*k+2] = propa(lazy[2*k+2], lazy[k]);
        }
        lazy[k] = eU;
    }

    T get(int a){
        return query(a, a+1);
    }

    void apply(int a, int b, T x){
        apply(a, b, x, 0, 0, n);
    }

    void apply(int a, int b, U x, int k, int l, int r){
        eval(k);

        if(b <= l || r <= a)return;
        if(a <= l && r <= b){
            lazy[k] = propa(lazy[k], x);
            eval(k);
        }else{
            apply(a, b, x, 2*k+1, l, (l+r)/2);
            apply(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = op(node[2*k+1], node[2*k+2]);
        }
    }

    T query(int a, int b){
        return query(a, b, 0, 0, n);
    }

    T query(int a, int b, int k, int l, int r){
        eval(k);
        if(b <= l || r <= a)return eT;

        if(a <= l && r <= b)return node[k];

        T vl = query(a, b, 2*k+1, l, (l+r)/2);
        T vr = query(a, b, 2*k+2, (l+r)/2, r);

        return op(vl, vr);
    }
};