//https://codeforces.com/contest/11/problem/D

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5+10;
const int MOD = 1e9 + 7 ;

int n,m,u,v;
set<int> adj[N];
ll sz[N];
ll ans=0;
ll dp[20][1<<19];
int vis[N];
int cur;
int val[N];

void dfs(int u,int msk, int p=-1){
    if(dp[u][msk]!=-1)
        return;
    vis[u]=1;
    ll rs=0;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        if(v==cur){
            rs++;
        }
        if(vis[v])
            continue;
        dfs(v,msk|1<<v,u);
        rs+=dp[v][msk|1<<v];
    }
    vis[u]=0;
    dp[u][msk]=rs;
}



int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        --u,--v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for(int i=0;i<n;i++){
        memset(dp, -1,sizeof(dp));
        cur=i;
        dfs(i,1<<i);
        ans+=dp[i][1<<i];
        for(int j=i+1;j<n;j++){
            if(adj[j].count(i)){
                adj[j].erase(i);
            }
        }
    }
    cout << ans/2;
    return 0;
}
