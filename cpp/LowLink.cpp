struct LowLink {
    int n;
    vector<int> ord, low;
    vector<pair<int,int>> bridges;//橋
    vector<int> arts;//関節点
    LowLink(const vector<vector<int>>& to):n(to.size()), ord(to.size()),low(to.size()){
        int k = 0;
        vector<bool> used(n);

        function<int(int,int,int)> dfs = [&](int depth, int k, int par){
            used[depth] = true;
            ord[depth] = k;
            low[depth] = k;
            ++k;

            bool is_art = false;
            int count = 0;
            for(int nxt : to[depth]){
                if(!used[nxt]){
                    ++count;
                    k = dfs(nxt, k+1, depth);
                    low[depth] = min(low[depth], low[nxt]);
                    if(par != -1 && ord[depth] <= low[nxt])is_art = true;
                    if(ord[depth] < low[nxt])bridges.push_back({min(depth, nxt), max(depth, nxt)});
                }else if(nxt != par){
                    low[depth] = min(low[depth], ord[nxt]);
                }
            }
            if(par == -1 && count >= 2)is_art = true;
            if(is_art)arts.push_back(depth);
            return k;
        };

        for(int i = 0;i < n; ++i){
            if(!used[i])k = dfs(i, k, -1);
        }
    }
};