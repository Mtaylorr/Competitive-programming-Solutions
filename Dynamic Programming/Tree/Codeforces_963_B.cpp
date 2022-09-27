//https://codeforces.com/contest/963/problem/B

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7   ;
const double eps = 1e-7;

int n;
vector<int> adj[N];
vector<int> dadj[N];
vector<int> tmp[N][2][3];
int dp[N][2];
int p;
bool cond=true;
vector<int> ord;
bool vis[N];
bool visst[N][2];

void dfs(int u,int st, int p=-1){
    if(visst[u][st])
        return ;
    visst[u][st]=1;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,1,u);
        dfs(v,0,u);
        if(dp[v][0] && dp[v][1]){
            tmp[u][st][2].pb(v);
        }else if(dp[v][0]){
            tmp[u][st][0].pb(v);
        }else if(dp[v][1]){
            tmp[u][st][1].pb(v);
        }
    }
    if(st==0){
        int szpair = tmp[u][st][0].size();
        if(szpair%2==0){
            dp[u][st]=1;
        }else {
            if(tmp[u][st][2].size()){
                int x = tmp[u][st][2].back();
                tmp[u][st][2].pop_back();
                tmp[u][st][0].pb(x);
                dp[u][st]=1;
            }
        }
    }else{
        int szpair = tmp[u][st][0].size();
        if(szpair%2==1){
            dp[u][st]=1;
        }else {
            if(tmp[u][st][2].size()){
                int x = tmp[u][st][2].back();
                tmp[u][st][2].pop_back();
                tmp[u][st][0].pb(x);
                dp[u][st]=1;
            }
        }
    }
}


void direct_graph(int u,int st, int p=-1){
    vis[u]=1;
    for(auto v:tmp[u][st][0]){
        dadj[u].pb(v);
        if(vis[v])
            continue;
        direct_graph(v,0,u);
    }
    for(auto v:tmp[u][st][1]){
        dadj[v].pb(u);
        if(vis[v])
            continue;
        direct_graph(v,1,u);
    }
    for(auto v:tmp[u][st][2]){
        dadj[v].pb(u);
        if(vis[v])
            continue;
        direct_graph(v,1,u);
    }
}


void toposort(int u=0){
    vis[u]=1;
    for(auto v:dadj[u]){
        if(vis[v])
            continue;
        toposort(v);
    }
    ord.pb(u);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> p;
        if(p==0){
            continue;
        }
        p--;
        adj[p].pb(i);
        adj[i].pb(p);
    }
    dfs(0,0);
    for(int i=0;i<n;i++){
        if(!dp[i][0] && !dp[i][1]){
            cout << "NO\n";
            return 0;
        }
    }
    direct_graph(0,0);
    memset(vis,0, sizeof(vis));
    for(int i=0;i<n;i++){
        if(vis[i])
            continue;
        toposort(i);
    }
    reverse(ord.begin(),ord.end());
    cout << "YES\n";
    for(auto u:ord){
        cout << u+1 << "\n";
    }
    return 0;
}
