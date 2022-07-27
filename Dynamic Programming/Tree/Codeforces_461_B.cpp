//https://codeforces.com/contest/461/problem/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e6 +5 ;
const int MOD = 1e9 + 7;

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
    ll ans=1;
    ll acc=u;
    while(v){
        if(v%2){
            ans=mul(ans,acc,mod);
        }
        acc = mul(acc,acc,mod);
        v/=2;
    }
    return ans;
}
ll  inv(ll u,ll mod=MOD){
    return powe(u,mod-2,mod);
}

vector<int> adj[N];
int n;
int col[N];
int x;
int dp[N][2];

void dfs(int u, int c){
    if(dp[u][c]!=-1)
        return ;
    dp[u][c]=0;
    if(col[u]==1 && c==0){
        return;
    }
    if(c==0 || (c==1 && col[u]==1)){
        dp[u][c]=1;
        for(auto v:adj[u]){
            dfs(v,0);
            dfs(v,1);
            dp[u][c]=mul(dp[u][c], add(dp[v][0], dp[v][1]));
        }
    }else{
        ll r=1;
        for(auto v:adj[u]){
            dfs(v,0);
            dfs(v,1);
            r=mul(r,add(dp[v][0], dp[v][1]));
        }
        dp[u][c]=0;
        for(auto v:adj[u]){
            dp[u][c]=add(dp[u][c] , mul(dp[v][1],mul(r, inv(add(dp[v][0],dp[v][1])))));
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    memset(dp, -1,sizeof(dp));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<n;i++){
        cin >> x;
        adj[x].pb(i);
    }
    for(int i=0;i<n;i++){
        cin >> col[i];
    }
    dfs(0,1);
    cout << dp[0][1];
    return 0;

}
