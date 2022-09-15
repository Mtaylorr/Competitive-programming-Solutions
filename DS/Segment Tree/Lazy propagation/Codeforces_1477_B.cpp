//https://codeforces.com/problemset/problem/1477/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2000 +5;
const int MOD = 1e9 + 7;

int t,n,q;
string s,f;
int l[N],r[N];
int tree[4*N];
int lazy[4*N];

void build(int id=0, int ns=0, int ne=n-1){
    lazy[id]=-1;
    if(ns==ne){
        tree[id]=f[ns]-'0';
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
    if(lazy[id]!=-1){
        tree[id] = (ne-ns+1)*lazy[id];
        if(ns!=ne){
            int l = 2*id+1;
            int r = l+1;
            lazy[l]=lazy[r]=lazy[id];
        }
        lazy[id]=-1;
    }
}

void upd(int qs, int qe, int v, int id=0, int ns=0, int ne=n-1){
    upd_lazy(id, ns, ne);
    if(ns> qe || qs>ne){
        return ;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]=v;
        upd_lazy(id, ns,ne);
        return;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, v, l, ns, md);
    upd(qs, qe, v, r, md+1, ne);
    tree[id]=tree[l]+tree[r];
}

int get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    upd_lazy(id, ns, ne);
    if(ns>qe || qs>ne){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs, qe, l, ns, md)+ get(qs, qe, r, md+1,ne);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n >> q;
        cin >> s;
        cin >> f;
        build();
        for(int i=0;i<q;i++){
            cin >> l[i] >> r[i];
            l[i]--;
            r[i]--;
        }
        bool cond=true;
        for(int i=q-1;i>=0;i--){
            int sm = get(l[i],r[i]);
            int sz = r[i]-l[i]+1;
            if(2*sm==sz){
                cond=false;
                break;
            }
            if(2*sm<sz){
                upd(l[i],r[i],0);
            }else{
                upd(l[i],r[i],1);
            }
        }

        for(int i=0;i<n;i++){
            int x  = get(i,i);
            if(x!=(s[i]-'0')){
                cond=false;
            }
        }
        if(cond){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
    return 0;


}
