#include <vector>
#include <queue>
using namespace std;
//参考:: https://qiita.com/Morifolium/items/6c8f0a188af2f9620db2

vector<int> topological_sort(vector<vector<int>> to, vector<int> count){
    // count::頂点の入力数
    int n = to.size();
    vector<int> sorted;
    queue<int> zero;

    for(int i = 0;i < n; ++i){
        if(count[i] == 0)zero.push(i);
    }

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