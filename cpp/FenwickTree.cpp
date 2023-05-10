template<typename T>
struct FenwickTree{
    int n;
    vector<T> data;

    FenwickTree(int n):n(n), data(n+1){}

    void add(int i, T x){
        assert(0 <= i && i < n);
        i++;
        while(i <= n){
            data[i] += x;
            i += i & -i;
        }
    }

    T get(int i) const {
        assert(0 <= i && i < n);
        return sum(i, i+1);
    }

    // sum[0, i)
    T sum(int i) const{
        assert(0 <= i && i <= n);
        T retu_sum = 0;
        while(i > 0){
            retu_sum += data[i];
            i -= i & -i;
        }

        return retu_sum;
    }

    // sum[l, r)
    T sum(int l, int r) const {
        assert(0 <= l && l <= n);
        assert(0 <= r && r <= n);
        return sum(r) - sum(l);
    }
};
