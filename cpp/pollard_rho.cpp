//require: gcd, miller_rabin
long long pollard_rho(long long n){
    if((n&1) == 0)return 2;
    if(miller_rabin(n))return n;

    auto f = [&](long long x) -> long long {
        return (__int128(x) * x + 1) % n;
    };

    long long step = 0;
    while(true){
        ++step;
        long long x = step, y = f(x);
        while(true){
            long long g = gcd(abs(x-y), n);
            if(g == 0 || g == n)break;
            if(g != 1)return g;
            x = f(x);
            y = f(f(y));
        }
    }
}

vector<long long> factorize(long long n){
    vector<long long> factors, tmp;
    tmp.push_back(n);
    while(tmp.size()){
        long long x = tmp.back();
        tmp.pop_back();
        long long v = pollard_rho(x);
        if(v == x){
            factors.push_back(v);
        }else{
            tmp.push_back(x/v);
            tmp.push_back(v);
        }
    }
    return factors;
}