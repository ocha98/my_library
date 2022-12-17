template<typename T>
T lcm(T a, T b){
    return a / gcd(a, b) * b;
}