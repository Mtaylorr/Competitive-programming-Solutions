//https://csacademy.com/ieeextreme18/task/kings-order/

#include <bits/stdc++.h>

using namespace std;
#define sd second
#define pb push_back
int a[1005];int vis[1005];
int in[1005];
vector<int> adj[1005];

int main() {
    int n, m;
    cin>>n>>m;
    for(int i = 1; i <=n; i++)  cin>>a[i];
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        in[v]++;
    }
    
    set<pair<int, int>> level;
    for(int i = 1; i<=n; i++) {
        if(!in[i])
            level.insert({a[i], i});
    }
    vector<int> ans;
    while(!level.empty()) {
        auto node = *level.begin();
        level.erase(level.begin());    
        ans.push_back(node.sd);
        for(auto child: adj[node.sd]) {
            in[child]--;
            if(!in[child])
                level.insert({a[child], child});
        }
    }
    if(ans.size() != n){
        cout<<-1;
    } else {
        for(auto p: ans)
            cout<<p<<' ';
    }
}
