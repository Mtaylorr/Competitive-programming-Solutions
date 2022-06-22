//https://codeforces.com/problemset/problem/1363/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n;
ll a[N];
int b[N],c[N];
int u,v;
int sz[N],toone[N], tozero[N];
vector<int> adj[N];
ll ans=0;

void solve(int u, int p=-1){

    for(auto v:adj[u]){
        if(v==p)
            continue;
        a[v]=min(a[v],a[u]);
        solve(v,u);

        toone[u]+=toone[v];
        tozero[u]+=tozero[v];
    }
    int x = min(toone[u], tozero[u]);
    ans+=a[u]*2*x;
    toone[u]-=x;
    tozero[u]-=x;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    int sumc=0, sumb=0;
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i] >> c[i];
        if(b[i]==1 && c[i]==0){
            tozero[i]++;
        }else if(b[i]==0 && c[i]==1){
            toone[i]++;
        }
        sumc+=c[i];
        sumb+=b[i];
    }
    if(sumc!=sumb){
        cout << -1;
        return 0;
    }
    for(int i=0;i<n-1;i++){
        cin >> u >> v;
        --u,--v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    solve(0);
    cout << ans << endl;
    return 0;

}
