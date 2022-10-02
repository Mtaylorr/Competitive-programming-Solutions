//https://codeforces.com/contest/825/problem/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD =998244353 ;
const double eps = 1e-7;

int n,m;
vector<int> adj[N];
bool vis[N];
bool done[N];
int u,v;
int nb;
int indeg[N];
int ans[N];
set<int> ss;

void dfs(int u){
    if(vis[u] || done[u])
        return ;
    vis[u]=1;
    nb++;
    dfs(u);
    for(auto v:adj[u]){
        dfs(v);
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> u >> v;
        adj[--v].pb(--u);
        indeg[u]++;
    }
    int mxcur=0;
    for(int i=0;i<n;i++){
        if(vis[i])
            continue;
        ss.clear();
        nb=0;
        dfs(i);
        mxcur+=nb;
        ss.insert(-i);
        int cur=mxcur;
        while(!ss.empty()){
            int u = -(*ss.begin());
            ss.erase(ss.begin());
            if(done[u])
                continue;
            done[u]=1;
            ans[u]=cur--;
            for(auto v:adj[u]){
                if(done[v])
                    continue;
                indeg[v]--;
                if(indeg[v]==0){
                    ss.insert(-v);
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        cout << ans[i] << " ";
    }
    return 0;

}

