//https://codeforces.com/contest/1714/problem/G
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e6 +5 ;
const int MOD = 1e9 + 7;

int t;
int n;
ll a[N];
ll A[N];
ll B[N];
ll b[N];
int p;
int r[N];
vector<ll> tmp;
vector<int> adj[N];

int get(int u){
    int p = lower_bound(tmp.begin(), tmp.end(), A[u])-tmp.begin();

    if(p==tmp.size())
        p--;
    else if(tmp[p]>A[u]){
        p--;
    }
    return p;
}

void solve(int u){
    tmp.pb(B[u]);
    if(u!=0){
        r[u]=get(u);
    }
    for(auto v:adj[u]){
        B[v]=B[u]+b[v];
        A[v]=A[u]+a[v];
        solve(v);
    }
    tmp.pop_back();
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        tmp.clear();
        cin >> n;
        for(int i=0;i<n;i++){
            A[i]=B[i]=0;
            adj[i].clear();
        }
        for(int i=1;i<n;i++){
            cin >> p >> a[i] >> b[i];
            adj[p-1].pb(i);
        }
        solve(0);
        for(int i=1;i<n;i++){
            cout << r[i] << " ";
        }
        cout << endl;
    }
    return 0;

}
