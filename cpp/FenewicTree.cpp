struct FenewicTree{
    int n;
    vector<long long> data;

    FenewicTree(int n):n(n), data(n+1){}

    void add(int i, long long x){
        i++;
        while(i <= n){
            data[i] += x;
            i += i & -i;
        }
    }

    long long sum(int i) const{
        i++;
        long long retu_sum = 0;
        while(i > 0){
            retu_sum += data[i];
            i -= i & -i;
        }
        
        return retu_sum;
    }
};