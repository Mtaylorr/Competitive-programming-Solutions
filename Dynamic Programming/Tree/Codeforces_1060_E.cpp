//https://codeforces.com/problemset/problem/1060/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

int n;
int u,v;
vector<int> adj[N];
int sz[N][2];
ll ans=0;
ll rs=0;
void calcdp(int u, int p=-1, int d=0){
    sz[u][d%2]++;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        calcdp(v,u,d+1);
        sz[u][0]+=sz[v][0];
        sz[u][1]+=sz[v][1];
    }
}

void dfs(int u, int p=-1, int d=0){
    int nb=0;
    ll sm=0;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        nb++;
        ans+=sz[v][d%2]*1ll*(n-sz[v][d%2]-sz[v][1-d%2]);
        //rs+=(sz[0][d%2]-sz[v][d%2]);
        ans+=(sz[v][1-d%2]*sm);
        sm+=(sz[v][1-d%2]);
    }
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u,d+1);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n-1;i++){
        cin >> u >> v;
        u--;v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    calcdp(0);
    dfs(0);
    rs = sz[0][0]*1ll*sz[0][1] ;
    cout << ans +rs<< endl;

    return 0;


}
