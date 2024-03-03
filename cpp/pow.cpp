long long pow(long long x, long long n){
    long long ret = 1;
    while (n > 0) {
        if (n & 1) ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}

long long pow(long long x, long long n, long long MOD){
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