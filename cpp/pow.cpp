template<typename T>
T pow(T x, T n){
    T ret = 1;
    while (n > 0) {
        if (n & 1) ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}

template<typename T>
T pow(T x, T n, T MOD){
    T ret = 1;
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