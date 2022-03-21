template <typename T>
vector<T> coor_compress(vector<T> coor){
    vector<T> cp = coor;
    sort(cp.begin(), cp.end());
    cp.erase(unique(cp.begin(), cp.end()), cp.end());
    int n = coor.size();
    for(int i = 0;i < n; ++i){
        coor[i] = lower_bound(cp.begin(), cp.end(), coor[i]) - cp.begin();
    }
    return coor;
}