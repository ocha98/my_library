struct CombinationMint {
    vector<Mint> fact, fact_inv;
    CombinationMint(int n):fact(n+1), fact_inv(n+1){
        fact[0] = 1;
        for(int i = 0;i < n; ++i){
            fact[i+1] = fact[i] * (i + 1);
        }

        fact_inv[n] = fact[n].inv();
        for(int i = n-1;i >= 0; --i){
            fact_inv[i] = fact_inv[i+1] * (i+1);
        }
    }

    Mint operator()(const int n, const int k){
        if(k < 0 || k > n)return 0;
        return fact[n]*fact_inv[k]*fact_inv[n-k];
    }
};