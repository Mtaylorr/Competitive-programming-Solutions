//https://codeforces.com/problemset/problem/280/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;

int n;
vector<int> adj[N];
int u,v;
long double ans=0;

void dfs(int u, int p=-1 ,int d=1){
    ans+=(1.0/(d*1.0));
    for(auto v:adj[u]){
        if(p==v)
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
    dfs(0);
    cout << fixed << setprecision(10) << ans << endl;



    return 0;

}
