template<typename T>
T gcd(T a, T b){
    if(a == 0)return b;
    if((a&1) == 0 && (b&1) == 0){
        return 2 * gcd(a>>1, b>>1);
    }
    if((a&1) == 0){
        return gcd(a>>1, b);
    }
    if((b&1) == 0){
        return gcd(a, b>>1);
    }
    return gcd(abs(a-b)>>1, min(a, b));
}