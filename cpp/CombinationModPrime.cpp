struct CombinationModPrime{
    vector<long long> fact, fact_inv;

    CombinationModPrime(int n): fact(n+1), fact_inv(n+1){
        fact[0] = 1;
        for(int i = 0;i < n; ++i){
            fact[i + 1] = (i+1) * fact[i] % MOD;
        }
        fact_inv[n] = mod_inverse(fact[n]);
        for(int i = n-1;i >= 0; --i){
            fact_inv[i] = fact_inv[i+1] * (i+1) % MOD;
        }
    }

    long long powMOD(long long x, long long n){
        long long ret = 1;
        x %= MOD;
        while (n > 0) {
            if (n & 1){
                ret *= x;
                ret %= MOD;
            }
            
            x *= x;
            x %= MOD;
            n >>= 1;
        }
        return ret;
    }

    long long mod_inverse(int x){
        return powMOD(x, MOD-2);
    }

    long long calc(long long n, long long k){
        if(n < k || n < 0 || k < 0)return 0;
        return fact[n] * (fact_inv[n-k] * fact_inv[k] % MOD)% MOD;
    }
};