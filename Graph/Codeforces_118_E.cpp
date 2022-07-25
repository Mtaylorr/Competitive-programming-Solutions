//https://codeforces.com/problemset/problem/118/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n,m;
set<int> adj[N];
vector<int> ansadj[N];
int u,v;
int in[N], out[N];
vector<pair<int,int> > ans;
bool vis[N];

void dfs(int u){
    if(vis[u])
        return ;
    vis[u]=1;
    while(adj[u].size()){
        int v = *adj[u].begin();
        adj[u].erase(adj[u].begin());
        ansadj[v].pb(u);
        adj[v].erase(u);
        ans.pb({u,v});
        dfs(v);
    }
}

void dfs2(int u){
    if(vis[u])
        return ;
    vis[u]=1;
    for(auto v:ansadj[u]){
        dfs2(v);
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> u >> v;
        u--,v--;

        adj[u].insert(v);
        adj[v].insert(u);
    }
    dfs(0);
    memset(vis, 0, sizeof(vis));
    dfs2(0);
    bool cond=true;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            cond=false;
        }
    }
    if(!cond){
        cout <<0 << endl;
        return 0;
    }
    for(auto u:ans){
        cout << u.fi+1 << " " << u.se+1 << endl;
    }
    return 0;

}
