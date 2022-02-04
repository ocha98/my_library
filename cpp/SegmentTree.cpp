template<class Type, Type (*op)(Type, Type)>
struct SegmentTree{
    vector<Type> data;
    Type e;
    int N = 1;
    SegmentTree(int n, Type e):SegmentTree(vector<Type>(n, e), e){}

    SegmentTree(vector<Type> v, Type e):e(e){
        int size = v.size();
        while(N < size)N *= 2;
        data = vector<Type>(2*N-1, e);
        for(int i = 0;i < size; ++i){
            set(i, v[i]);
        }
    }

    void set(int k, Type a){
        k += N-1;
        data[k] = a;
        while(k > 0){
            k = (k-1) / 2;
            data[k] = op(data[2*k + 1], data[2*k + 2]);
        }
    }

    Type query(int a, int b){// [a, b)
        return query(a, b, 0, 0, N);
    }

    Type query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l)return e;
        if(a <= l && r <= b){
            return data[k];
        }else{
            Type val_l = query(a, b, 2*k + 1, l, (l+r)/2);
            Type val_r = query(a, b, 2*k + 2, (l+r)/2, r);
            return op(val_l, val_r);
        }
    }
};