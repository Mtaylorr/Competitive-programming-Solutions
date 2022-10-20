//https://codeforces.com/problemset/problem/1557/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 6e5 + 5, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

vector<int> ranges[N];
set<int> distincts;
map<int,int> code;
int cn;
int n,m;
int l[N], r[N];
int par[N];

typedef pair<int,int> dtype;
dtype OUT_OF_RANGE = {0,-1};
dtype tree[4 * N];
dtype lazy[4*N];
dtype NULL_Lazy = {0,-1};

dtype mrg(dtype &a,dtype & l, dtype &r){
    return a=max(l,r);
}
bool has_lazy(int id){ return lazy[id]!=NULL_Lazy; }

void rem_lazy(int id){ lazy[id]=NULL_Lazy;}

void unlazy(int id, int ns, int ne){tree[id]=max(tree[id],lazy[id]);}

void propagate(int id, int chld){lazy[chld]=max(lazy[chld],lazy[id]);}

void upd_lazy(int id ,int ns, int ne){
    if(has_lazy(id)){
        unlazy(id, ns, ne);
        if(ns!=ne){
            int l = 2*id+1;
            int r = 2*id+2;
            propagate(id, l);
            propagate(id, r);
        }
        rem_lazy(id);
    }
}

void build(int id = 0, int ns = 0, int ne = cn - 1) {
    lazy[id]=NULL_Lazy;
    if (ns == ne) {
        tree[id] = OUT_OF_RANGE;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    mrg(tree[id],tree[l],tree[r]);
}

void upd(int qs, int qe, dtype v, int id = 0, int ns = 0, int ne = cn - 1) {
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]=v;
        upd_lazy(id, ns, ne);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(qs, qe, v, l, ns, md);
    upd(qs, qe, v, r, md+1, ne);
    mrg(tree[id],tree[l],tree[r]);
}


dtype query(int qs, int qe, int id = 0, int ns = 0, int ne = cn - 1) {
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return OUT_OF_RANGE;
    }
    if(qs<=ns && qe>=ne){
        return  tree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    dtype la = query(qs, qe, l, ns, md);
    dtype ra = query(qs, qe, r, md + 1, ne);
    dtype ca;
    mrg(ca, la, ra);
    return ca;
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(par,-1, sizeof(par));
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int x;
        cin >> x >> l[i] >> r[i];
        ranges[x].pb(i);
        distincts.insert(l[i]);
        distincts.insert(r[i]);
    }
    for(auto u:distincts){
        code[u]=cn++;
    }
    for(int i=0;i<m;i++){
        l[i]=code[l[i]];
        r[i]=code[r[i]];
    }
    build();
    int ans=0;
    int lst=-1;
    for(int i=1;i<=n;i++){
        int mx=1;
        for(auto u:ranges[i]){
            pair<int,int> p =query(l[u],r[u]);
            p.fi++;
            if(p.fi>mx){
                mx=p.fi;
                par[i]=p.se;
            }
        }
        if(ans<mx){
            ans=mx;
            lst=i;
        }
        ans=max(ans, mx);
        for(auto u:ranges[i]){
            upd(l[u],r[u],{mx,i});
        }
    }
    cout << n-ans << endl;
    set<int> path;
    while(lst!=-1){
        path.insert(lst);
        lst=par[lst];
    }
    for(int i=1;i<=n;i++){
        if(path.count(i)==0){
            cout << i << " ";
        }
    }

    return 0;

}
