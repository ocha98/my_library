vector<int> scc(const vector<vector<int>>& to){
    const int n = to.size();
    vector<int> ord(n, -1), low(n);
    vector<int> group(n, -1);
    int group_num = 0;
    int now_ord = 0;
    vector<int> st;
    st.reserve(n);
    auto dfs = [&](auto& self, int v)->void{
        low[v] = ord[v] = now_ord;
        ++now_ord;
        st.push_back(v);

        for(int nxt: to[v]){
            if(ord[nxt] == -1){
                self(self, nxt);
                low[v] = min(low[v], low[nxt]);
            }else if(group[nxt] == -1){
                low[v] = min(low[v], ord[nxt]);
            }
        }

        if(ord[v] == low[v]){
            while(true){
                int u = st.back();
                st.pop_back();
                group[u] = group_num;
                if(v == u)break;
            }
            ++group_num;
        }
    };

    for(int i = 0;i < n; ++i){
        if(ord[i] == -1){
            dfs(dfs, i);
        }
    }

    return group;
}