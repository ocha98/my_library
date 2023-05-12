struct Eratosthenes{
    private:
    vector<int> min_factor;
    vector<int> prev_divisor;
    vector<int> primes;
    vector<int> min_factor_e;
    const int MAX;

    public:
    Eratosthenes(int n):min_factor(n+1), min_factor_e(n+1), prev_divisor(n+1), MAX(n) {
        min_factor[1] = 1;
        for(int i = 2;i <= n; ++i){
            if(min_factor[i] == 0){
                min_factor[i] = i;
                primes.push_back(i);
                min_factor_e[i] = 1;
            }

            for(int p: primes){
                if(p*i > n || p > min_factor[i])break;
                min_factor[p*i] = p;
                if(p == min_factor[i]){
                    min_factor_e[p*i] = min_factor_e[i]+1;
                    prev_divisor[p*i] = prev_divisor[i];
                }else{
                    min_factor_e[p*i] = 1;
                    prev_divisor[p*i] = i;
                }
            }
        }
    }

    vector<int> get_primes() const {
        return primes;
    }

    bool is_prime(int n) const {
        assert(0 < n && n <= MAX);
        if(n == 1 || n == 0)return false;
        return n == min_factor[n];
    }

    vector<pair<int,int>> factorize(int n) const {
        assert(1 <= n && n <= MAX);
        vector<pair<int,int>> resu;
        while(n > 1){
            const int p = min_factor[n];
            const int e = min_factor_e[n];
            resu.emplace_back(make_pair(p, e));
            n = prev_divisor[n];
        }
        return resu;
    }

    vector<int> divisors(int n) const {
        assert(1 < n && n <= MAX);

        vector<int> resu = {1};
        vector<pair<int,int>> factors = factorize(n);
        for(const pair<int,int>& pe : factors){
            const int p = pe.first;
            const int e = pe.second;

            const int s = resu.size();
            for(int i = 0;i < s; ++i){
                int v = 1;
                for(int ii = 0;ii < e; ++ii){
                    v *= p;
                    resu.push_back(resu[i]*v);
                }
            }
        }

        return resu;
    }
};