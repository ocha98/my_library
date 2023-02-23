long long euler_phi(long long n){
    long long retu = n;
    for(long long i = 2;i*i <= n; ++i){
        if(n%i == 0){
            retu -= retu/i;
            while(n%i == 0)n /= i;
        }
    }
    if(n > 1)retu -= retu/n;
    return retu;
}
