//https://www.spoj.com/problems/HORRIBLE/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(3e6) + 3;
const int MOD = int(1e9) + 7;

ll tree[N];
ll lazy[N];
ll T,n,c,t,p,q,v;

void upd_lazy(int id ,ll ns, ll ne){
    tree[id]+=lazy[id]*(ne-ns+1);
    if(ns!=ne){
        int l = 2*id+1;
        int r = 2*id+2;
        lazy[l]+=lazy[id];
        lazy[r]+=lazy[id];
    }
    lazy[id]=0;
}

void upd(int qs, int qe, ll v, int id=0, int ns=1 , int ne=n){
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]=v;
        upd_lazy(id, ns, ne);
        return;
    }
    int l = 2*id+1;
    int r = 2*id+2;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, v, l, ns, md);
    upd(qs, qe, v, r, md+1, ne);
    tree[id] = tree[l]+tree[r];
}

ll query(int qs, int qe, int id=0, int ns=1, int ne=n){
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return  tree[id];
    }
    int l = 2*id+1;
    int r = 2*id+2;
    int md = ns+(ne-ns)/2;
    ll v1 = query(qs, qe, l, ns, md);
    ll v2 = query(qs, qe, r, md+1, ne);
    return v1+v2;
}

int main() {
    FAST;
    cin >> T;
    while(T--){
        cin >> n >> c;
        for(int i=0;i<=4*n;i++){
            tree[i]=0;
            lazy[i]=0;
        }
        while(c--){
            cin >> t;
            if(t==0){
                cin >> p >> q >> v;
                upd(p,q,v);
            }else{
                cin >> p >> q;
                cout << query(p,q) << endl;
            }
        }

    }
    return 0;
}
