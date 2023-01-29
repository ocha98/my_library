struct RollingHash {
    static const long long mod = (1LL << 61) - 1;
    const long long mask30 = (1LL << 30) - 1;
    const long long mask31 = (1LL << 31) - 1;
    static long long base;
    vector<long long> hash, power;

    RollingHash(const string& s){
        int n = s.length();
        hash.assign(n+1, 0);
        power.assign(n+1, 0);
        power[0] = 1;
        for(int i = 0;i < n; ++i){
            power[i+1] = mul(power[i], base);
            hash[i+1] = mul(hash[i], base) + s[i];
            if(hash[i+1] >= mod)hash[i+1] -= mod;
        }
    }

    long long get(int  l, int r)  {
        long long resu = hash[r] + mod - mul(hash[l], power[r - l]);
        if(resu >= mod)resu -= mod;
        return resu;
    }

    long long link(long long h1, long long h2, int len_h2){
        long long resu = mul(h1, power[len_h2]) + h2;
        if(resu >= mod)resu -= mod;
        return resu;
    }

    long long mul(long long a, long long b){
        // a*b mod
        long long au = a >> 31;
        long long ad = a & mask31;
        long long bu = b >> 31;
        long long bd = b & mask31;
        long long mid = ad * bu + au * bd;
        long long midu = mid >> 30;
        long long midd = mid & mask30;

        long long x = au * bu * 2 + midu + (midd << 31) + ad * bd;

        long long xu = x >> 61;
        long long xd = x & mod;
        long long res = xu + xd;
        if (res >= mod) res -= mod;
        return res;
    }

    long long pow(long long x, long long n){
        long long ret = 1;
        x %= mod;
        while (n > 0) {
            if (n & 1){
                ret = mul(ret, x);
            }

            x = mul(x, x);
            n >>= 1;
        }
        return ret;
    }
};

long long RollingHash::base = 37;

void set_base() {
    mt19937 rd{(unsigned int)time(NULL)};
    uniform_int_distribution<long long> dist(2, RollingHash::mod -1);
    for(int i = 0;i < 100; ++i){
        long long k = dist(rd);
        long long tmp = pow(RollingHash::base, k);
        if(tmp > 'z'){
            RollingHash::base = tmp;
            break;
        }
    }
}