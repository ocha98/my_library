vector<pair<long long,int>> factorization(long long x){
    vector<pair<long long,int>> resu;
    for(long long i = 2;i*i <= x; ++i){
        if(x%i)continue;
        int e = 0;
        while(x%i == 0){
            ++e;
            x /= i;
        }
        resu.push_back({i, e});
    }

    if(x != 1){
        resu.push_back({x, 1});
    }

    return resu;
}
