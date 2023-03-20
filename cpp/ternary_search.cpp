// 黄金探索
template<typename T>
pair<T,T> ternary_search(T l, T r, function<T(T)> f, bool maximum){
    const double phi = (1.0 + sqrt(5.0)) / 2.0;
    double c1 = l + (r-l)/(phi + 1);
    double c2 = r - (r-l)/(phi + 1);
    // (r-l) <= 1e18, 許容誤差1e-9の場合の回数
    for(int ii = 0;ii < 140; ++ii){
        if(!maximum ^ (f(c1) < f(c2))){
            l = c1;
            c1 = c2;
            c2 = r - (r-l)/(phi + 1);
        }else{
            r = c2;
            c2 = c1;
            c1 = l + (r-l)/(phi + 1);
        }
    }

    return make_pair(l, r);
}