template<typename T>
vector<vector<T>> rot_right(const vector<vector<T>>& a){
    const int n = a.size();
    const int m = a[0].size();

    vector<vector<T>> resu(m, vector<T>(n));
    for(int i = 0;i < n; ++i){
        assert(a[i].size() == m);
        for(int j = 0;j < m; ++j){
            resu[j][n-1-i] = a[i][j];
        }
    }

    return resu;
}

template<typename T>
vector<vector<T>> rot_left(const vector<vector<T>>& a){
    const int n = a.size();
    const int m = a[0].size();

    vector<vector<T>> resu(m, vector<T>(n));
    for(int i = 0;i < n; ++i){
        assert(a[i].size() == m);
        for(int j = 0;j < m; ++j){
            resu[m-1-j][i] = a[i][j];
        }
    }

    return resu;
}