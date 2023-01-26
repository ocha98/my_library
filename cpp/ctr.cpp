template<typename T>
pair<T,T> ctr(const vector<T>& rs, const vector<T>& ms){
    assert(rs.size() == ms.size());

    int n = rs.size();
    T r0 = 0;
    T m0 = 1;
    for(int i = 0;i < n; ++i){
        T m1 = ms[i];
        T r1 = rs[i];
        r1 = (r1%m1 + m1)%m1;

        if(r0 < r1){
            swap(r0, r1);
            swap(m0, m1);
        }

        T g = __gcd(m0, m1);
        if(r0%g != r1%g){
            return pair<T,T>(-1, -1);
        }

        auto[x, y] = extgcd(m0, m1);
        T u1 = (m1 / g);
        T v = (r1 - r0) / g % u1 * x % u1;

        r0 += v * m0;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }

    return pair<T,T>(r0, m0);
}
