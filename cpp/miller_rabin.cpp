// require: pow
bool miller_rabin(long long n){
    if(n == 2)return true;
    if(n <= 1 || (n&1) == 0)return false;

    // cf. https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Deterministic_variants_of_the_test
    vector<long long> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    long long s = 0,t = n-1;
    while((t&1) == 0){
        s++;
        t >>= 1;
    }

    for(long long a : bases){
        if(a > n-1)break;

        if(pow<__int128>(a, t, n) == 1)continue;

        bool ok = false;
        long long x = pow<__int128>(a, t, n);
        for(int i = 0;i < s; ++i){
            if(x == n-1){
                ok = true;
            }
            x = __int128(x)*x%n;
        }

        if(!ok){
            return false;
        }
    }
    return true;
}