//https://codeforces.com/problemset/problem/877/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD =  998244353;

int n;
vector<int> adj[N];
vector<int> nodes;
int p;
int t[N],v;
string s;
int q;
int tin[N], tout[N];
int lazy[8*N];
int tree[8*N];

void dfs(int u=0){
    tin[u]=nodes.size();
    nodes.pb(u);
    for(auto v:adj[u]){
        dfs(v);
    }
    tout[u]=nodes.size();
    nodes.pb(u);
}

void build(int id=0,int ns=0, int ne=2*n-1){
    if(ns==ne){
        tree[id]=t[nodes[ns]];
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1,ne);
    tree[id]=tree[l]+tree[r];
}

void upd_lazy(int id, int ns, int ne){
    lazy[id]%=2;
    if(lazy[id]){
        tree[id] = ne-ns +1 - tree[id];
        if(ns!=ne){
            int l = 2*id+1;
            int r = l+1;
            lazy[l]+=lazy[id];
            lazy[r]+=lazy[id];
        }
    }
    lazy[id]=0;
}

void upd(int qs, int qe, int id=0, int ns=0, int ne=2*n-1){
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return ;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]++;
        upd_lazy(id, ns, ne);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, l, ns, md);
    upd(qs, qe, r, md+1,ne);
    tree[id]=tree[l]+tree[r];
}

int get(int qs, int qe, int id=0, int ns=0, int ne=2*n-1){
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs, qe, l, ns, md) + get(qs, qe, r, md+1, ne);
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<n;i++){
        cin >> p;
        adj[--p].pb(i);
    }
    dfs();
    for(int i=0;i<n;i++){
        cin >> t[i];
    }
    build();
    cin >> q;
    while(q--){
        cin >> s >> v;
        v--;
        if(s[0]=='g'){
            cout << get(tin[v], tout[v])/2 << endl;
        }else{
            upd(tin[v], tout[v]);
        }
    }
    return 0;
}
