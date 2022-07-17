//https://codeforces.com/contest/1705/problem/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int t;
int n;
int a[N];
int freq[N];
int tree[4*N];
int lazy[4*N];
int q;
int curmax;
void upd_lazy(int id, int ns, int ne){
    if(lazy[id]%2) {
        tree[id] = (ne - ns + 1) - tree[id];
    }
    if(ns!=ne){
        int l=2*id+1;
        int r = l+1;
        lazy[l]+=lazy[id];
        lazy[r]+=lazy[id];
    }
    lazy[id]=0;
}

void build(int id=0, int ns=0, int ne=3e5){
    if(ns==ne){
        tree[id]=freq[ns]%2;
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1,ne);
    tree[id]=tree[l]+tree[r];
}
int get(int qs, int qe,int id=0, int ns=0, int ne=3e5){
    upd_lazy(id, ns, ne);
    if(ns>qe || qs>ne){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs,qe, l, ns, md)+get(qs,qe,r, md+1, ne);
}

int getsz(int qp, int target, int id=0, int ns=0, int ne=3e5){
    upd_lazy(id, ns, ne);
    if(ne<qp){
        return ne;
    }
    if(ns>=qp && tree[id]==(ne-ns+1)*target){
        return ne;
    }
    if(ns==ne){
        return ns-1;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    int vall = getsz(qp, target, l, ns, md);
    if (vall==md){
        return getsz(qp, target, r, md+1,ne);
    }
    return vall;
}

int getinvsz(int id=0, int ns=0, int ne=3e5){
    upd_lazy(id, ns, ne);
    if(tree[id]==0){
        return ns;
    }
    if(ns==ne){
        return ne+1;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    int valr = getinvsz(r, md+1, ne);
    if (valr==md+1){
        return getinvsz(l, ns,md);
    }
    return valr;
}

void upd(int qs, int qe, int v,int id=0, int ns=0,int ne=3e5){
    upd_lazy(id, ns, ne);
    if(ns>qe || qs>ne){
        return;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]+=v;
        lazy[id]=(lazy[id]%2 + 2 )%2;
        upd_lazy(id, ns,ne);
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, v, l, ns, md);
    upd(qs, qe, v, r, md+1, ne);
    tree[id]=tree[l]+tree[r];
}



int k,l;


void add(int u){
    int l = getsz(u,1);
    upd(u, l+1,1);
    curmax=max(curmax,l+1);
}

void rem(int u){
    int l = getsz(u,0);
    upd(u, l+1,1);
    if(l+1==curmax){
        curmax--;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for(int i=0;i<n;i++){
        cin >> a[i];
        freq[a[i]]++;
    }
    for(int i=1;i<=3e5;i++){
        int x = freq[i]/2;
        freq[i]=freq[i]%2;
        freq[i+1]+=x;
        if(freq[i]){
            curmax=i;
        }
    }
    build();
    while(q--){
        cin >> k >> l;
        k--;
        rem(a[k]);
        a[k]=l;
        add(a[k]);
        cout << getinvsz()-1 << endl;
    }
    return 0;

}
