// \sum_{i = 0}^{n-1} floor(\frac{a \times i + b}{m})
long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if(a >= m){
        ans += a/m * ((n-1)*n/2);
        a %= m;
    }
    if(b >= m){
        ans += b/m * n;
        b %= m;
    }

    long long y_max = (a*n + b)/m;
    long long x_max = m*y_max - b;

    if(y_max == 0)return ans;

    ans += (n - (x_max + a-1)/a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max%a)%a);

    return ans;
}
