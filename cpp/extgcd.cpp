template<typename T>
pair<T,T> extgcd(T a, T b){
    // ax + by = gcd(a, b)
    if(a == 0){
        return pair<T,T>(0, 1);
    }else if(b == 0){
        return pair<T,T>(1, 0);
    }

    T q = a/b;
    T r = a%b;

    auto [s, t] = extgcd(b, r);

    T y = s - q*t;
    return pair<T,T>(t, y);
}