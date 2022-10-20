//https://codeforces.com/problemset/problem/708/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 5, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int n;
int sz[N];
vector<int> adj[N];
int tree[N];
int u, v;
int cent;
int ans[N];

void upd(int x, int v){
    for(;x<=n;x+=(x)&(-x)){
        tree[x]+=v;
    }
}
int get(int x){
    if(x<=0){
        return 0;
    }
    int rs=0;
    for(;x;x-=(x)&(-x)){
        rs+=tree[x];
    }
    return rs;
}

int buildsz(int u, int p = -1) {
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v == p)
            continue;
        buildsz(v, u);
        sz[u] += sz[v];
    }
}

int getcen(int u, int p = -1) {
    for (auto v: adj[u]) {
        if (v == p)
            continue;
        if (sz[v] > (n/2)) {
            return getcen(v,u);
        }
    }
    return u;
}

void remsz(int u, int p=-1){
    upd(sz[u],-1);
    for (auto v: adj[u]) {
        if (v == p)
            continue;
        remsz(v,u);
    }
}

void addsz(int u, int p=-1){
    upd(sz[u],+1);
    for (auto v: adj[u]) {
        if (v == p)
            continue;
        addsz(v,u);
    }
}

void calcans(int u, int p=-1){
    int mx = n-sz[u];
    int to_rem = mx-n/2;
    //cout << u << " " << sz[u]  << " " << to_rem << endl;
    int sm = get(n/2)-get(to_rem-1);
    if(sm){
        ans[u]=1;
    }
    for(auto v:adj[u]){
        if(v==p)
            continue;
        calcans(v,u);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    buildsz(0);
    cent = getcen(0);
    buildsz(cent);
    ans[cent]=1;
    for (int i = 0; i < n; i++) {
        upd(sz[i],1);
    }
    for(auto v:adj[cent]){
        remsz(v,cent);
        upd(n-sz[v],1);
        calcans(v,cent);
        upd(n-sz[v],-1);
        addsz(v,cent);
    }
    for(int i=0;i<n;i++){
        cout << ans[i] << " ";
    }
    return 0;

}
