template<typename T>
struct FenwickTree{
    int n;
    vector<T> data;

    FenwickTree(int n):n(n), data(n+1){}

    void add(int i, T x){
        assert(i < n);
        i++;
        while(i <= n){
            data[i] += x;
            i += i & -i;
        }
    }

    T get(int i) const {
        assert(i < n);
        return sum(i, i+1);
    }

    // sum[0, i)
    T sum(int i) const{
        assert(i <= n);
        T retu_sum = 0;
        while(i > 0){
            retu_sum += data[i];
            i -= i & -i;
        }

        return retu_sum;
    }

    // sum[l, r)
    T sum(int l, int r) const {
        assert(l <= n);
        assert(r <= n);
        return sum(r) - sum(l);
    }
};
