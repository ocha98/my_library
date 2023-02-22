vector<int> scc(const vector<vector<int>>& to) {
    int n = to.size();
    vector<int> ordv;
    vector<bool> visited(n);
    function<void(int)> dfs = [&](int depth){
        visited[depth] = true;
        for(int nxt: to[depth]){
            if(visited[nxt])continue;
            dfs(nxt);
        }
        ordv.push_back(depth);
    };

    for(int i = 0;i < n; ++i){
        if(visited[i])continue;
        dfs(i);
    }

    vector<vector<int>> inv_to(n);
    for(int i = 0;i < n; ++i){
        for(int v : to[i]){
            inv_to[v].push_back(i);
        }
    }

    vector<int> group(n);
    int k = 1;
    function<void(int)> rdfs = [&](int depth){
        group[depth] = k;
        for(int nxt : inv_to[depth]){
            if(group[nxt])continue;
            rdfs(nxt);
        }
    };

    reverse(ordv.begin(), ordv.end());
    for(int v : ordv){
        if(group[v])continue;
        rdfs(v);
        ++k;
    }

    return group;
}
