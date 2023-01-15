vector<int> topological_sort(vector<vector<int>>& to){
    int n = to.size();
    vector<int> count(n);

    for(int i = 0;i < n; ++i){
        for(int v: to[i]){
            count[v]++;
        }
    }

    queue<int> zero;
    for(int i = 0;i < n; ++i){
        if(count[i] == 0)zero.push(i);
    }

    vector<int> sorted;
    while(!zero.empty()){
        int v = zero.front();
        zero.pop();
        for(int u : to[v]){
            count[u]--;
            if(count[u] == 0)zero.push(u);
        }
        sorted.push_back(v);
    }

    return sorted;
}