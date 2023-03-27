vector<long long> divisors(long long n){
    vector<long long> ans;
    for(long long i = 1;i*i <= n; ++i){
        if(n%i)continue;
        if(i*i == n){
            ans.push_back(i);
        }else{
            ans.push_back(i);
            ans.push_back(n/i);
        }
    }

    return ans;
}
