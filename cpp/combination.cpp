#include<bits/stdc++.h>
using namespace std;

long long c(long long n, int x){
    long long retu = 1;
    x = min<long long>(x, n-x);
    for(int i = 1;i <= x; ++i){
        retu *= n;
        retu /= i;
        --n;
    }
    return retu;
}

// ===cMOD===

long long powMOD(long long x, long long n, long long MOD){
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

long long mod_inverse(int x, int mod){
    /* 
    参考:https://qiita.com/drken/items/6b4031ccbb2cab7436f3
    */

   return powMOD(x, mod-2, mod);
}


long long cMOD(long long n, long long k, long long mod){
    long long factn = 1;
    k = min(k, n-k);
    n %= mod;
    for(int i = 0; i < k; ++i){
        factn *= n-i;
        factn %= mod;
    }
    long long factk = 1;
    for(int i = 1; i <= k; ++i){
        factk *= i;
        factk %= mod;
    }


    return factn * mod_inverse(factk, mod) % mod;
}

struct CombinationModuloPrime{
    int MOD;
    vector<long long> fact, fact_inv;

    CombinationModuloPrime(int n, int mod): fact(n+1), fact_inv(n+1), MOD(mod){
        fact[0] = 1;
        for(int i = 0;i < n; ++i){
            fact[i + 1] = (i+1) * fact[i] % MOD;
        }
        fact_inv[n] = mod_inverse(fact[n], MOD);
        for(int i = n-1;i >= 0; --i){
            fact_inv[i] = fact_inv[i+1] * (i+1) % MOD;
        }
    }

    long long powMOD(long long x, long long n, long long MOD){
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

    long long mod_inverse(int x, int mod){
        return powMOD(x, mod-2, mod);
    }

    long long calc(long long n, long long k){
        if(n < k || n < 0 || k < 0)return 0;
        return fact[n] * (fact_inv[n-k] * fact_inv[k] % MOD)% MOD;
    }
};

