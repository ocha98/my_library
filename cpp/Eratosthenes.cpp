struct Eratosthenes{
    vector<int> min_factor;

    Eratosthenes(int n):min_factor(n+1) {
        min_factor[1] = 1;
        for(int i = 2;i <= n; ++i){
            if(min_factor[i] != 0)continue;
            for(int j = i;j <= n;j += i){
                min_factor[j] = i;
            }
        }
    }

    bool is_prime(int n){
        if(n == 1 || n == 0)return false;
        return n == min_factor[n];
    }

    vector<pair<int,int>> factorize(int n){
        vector<pair<int,int>> resu;
        while(n > 1){
            int p = min_factor[n];
            int e = 0;
            while(min_factor[n] == p){
                n /= p;
                e++;
            }
            resu.push_back(make_pair(p, e));
        }
        return resu;
    }

    vector<int> divisors(int n){
        vector<int> resu = {1};
        vector<pair<int,int>> factors = factorize(n);
        for(pair<int,int> pe : factors){
            int p = pe.first;
            int e = pe.second;

            int s = resu.size();
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
