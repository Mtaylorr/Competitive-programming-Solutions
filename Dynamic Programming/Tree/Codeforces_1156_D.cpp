//https://codeforces.com/problemset/problem/1156/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 +7 ;

int n;
vector<pair<int ,int> > adj[N];
ll dp[N][4];
int u,v,w;
ll ans=0;

void dfs(int u, int p=-1){
    ll res=0;
    ll res0=0;
    for(auto v:adj[u]){
        if(v.fi==p)
            continue;
        dfs(v.fi,u);
        if(v.se==0){
            res+=2*(1+dp[u][0])*(1+dp[v.fi][0]);
            res+=(dp[u][3]+dp[u][1])*(1+dp[v.fi][0]);
            res+=(1+dp[u][0])*(dp[v.fi][3]+dp[v.fi][1]);
            dp[u][0]+=(1+dp[v.fi][0]);
            dp[u][3]+=(dp[v.fi][3]);
            dp[u][3]+=(dp[v.fi][1]);
        }else{
            res+=2*(1+dp[u][1])*(1+dp[v.fi][1]);
            res+=(dp[u][2]+dp[u][0])*(1+dp[v.fi][1]);
            res+=(1+dp[u][1])*(dp[v.fi][2]+dp[v.fi][0]);
            dp[u][1]+=(1+dp[v.fi][1]);
            dp[u][2]+=dp[v.fi][2];
            dp[u][2]+=dp[v.fi][0];
        }
    }
    res+=res0;
    ans+=res;
}


int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        scanf("%d%d%d",&u,&v,&w);
        --u,--v;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    dfs(0);
    cout << ans;
    return 0;

}
