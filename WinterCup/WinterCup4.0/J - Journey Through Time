#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353  ;

int n,m,x,u,v;
ll d[N];
vector<int> adj[N];
set<int> special;
ll ans;
int dp[N];
int mx[N];

void dfs(int u, int p=-1){
    if(special.count(u)){
        dp[u]=1;
    }
    vector<int> ds;
    mx[u]=d[u];
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u);
        dp[u]=max(dp[u],dp[v]);
        if(dp[v]){
            mx[u]=max(mx[u],mx[v]);
            ds.push_back(mx[v]);
        }
    }
    sort(ds.rbegin(), ds.rend());
    for(int i=1;i<ds.size();i++){
        ans+=ds[i];
    }
    if(u==0){
        ans+=mx[u];
    }
}

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d",&x);
        --x;
        special.insert(x);
    }
    for(int i=0;i<n;i++){
        scanf("%lld",&d[i]);
    }
    ans=0;
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        --u,--v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0);
    cout << ans ;

    return 0;
}
