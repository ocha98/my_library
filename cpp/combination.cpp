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