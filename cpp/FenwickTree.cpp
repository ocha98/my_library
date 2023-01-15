template<typename T>
struct FenwickTree{
    int n;
    vector<T> data;

    FenwickTree(int n):n(n), data(n+1){}

    void add(int i, T x){
        i++;
        while(i <= n){
            data[i] += x;
            i += i & -i;
        }
    }

    // sum[0, i)
    T sum(int i) const{
        T retu_sum = 0;
        while(i > 0){
            retu_sum += data[i];
            i -= i & -i;
        }

        return retu_sum;
    }

    // sum[l, r)
    T sum(int l, int r) const {
        return sum(r) - sum(l);
    }
};