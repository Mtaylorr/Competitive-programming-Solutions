//https://codeforces.com/contest/1000/problem/F
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7  ;
const double eps = 1e-7;

int ql[N], qr[N],qa[N];
pair<int,int>  tree[4*N];
int n,q;
int a[N];
int nxt[N];
int pos[N];
vector<int> qi[N];

pair<int,int> mrg(pair<int,int> a,pair<int, int> b){
    if(a.fi<b.fi){
        return a;
    }
    return b;
}

void upd(int qp, int v,int id=0, int ns=0, int ne=n-1){
    if(ns> qp || ne<qp)
        return ;
    if(ns==ne){
        tree[id]={v,ns};
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qp, v, l, ns, md);
    upd(qp, v, r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

pair<int,int> get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(qs>ne || qe<ns)
        return {n,0};
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return mrg(get(qs, qe, l,ns,md), get(qs, qe, r, md+1,ne));
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(pos, -1, sizeof(pos));
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        nxt[i]=pos[a[i]];
        pos[a[i]]=i;
    }
    cin >> q;
    for(int i=0;i<q;i++){
        cin >> ql[i] >> qr[i];
        ql[i]--,qr[i]--;
        qi[qr[i]].pb(i);
    }
    for(int i=0;i<n;i++){
        if(nxt[i]!=-1){
            upd(nxt[i],n);
        }
        upd(i, nxt[i]);
        for(auto u:qi[i]){
            int l = ql[u];
            pair<int,int>p =  get(l, i);
            if(p.fi<l){
                qa[u]=a[p.se];
            }else{
                qa[u]=0;
            }
        }
    }
    for(int i=0;i<q;i++){
        cout << qa[i] << "\n";
    }

    return 0;
}
