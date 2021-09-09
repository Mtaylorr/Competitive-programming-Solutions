//https://codeforces.com/contest/438/problem/D
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;

typedef long long ll;

struct node{
    ll sum;
    int mx;
    node(){
        sum=mx=0;
    }
    node(ll s, int m){
        sum=s;
        mx=m;
    }
};

node tree[4*N];
int n;
int a[N];

node mrg(node& a, node& b){
    return {a.sum+b.sum, max(a.mx, b.mx)};
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]={a[ns], a[ns]};
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}


void updrng(int qs, int qe, int x, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || ne<qs)
        return ;
    if(tree[id].mx<x)
        return ;
    if(ns==ne){
        int v = tree[id].sum;
        tree[id]= {v%x, v%x};
        return;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    updrng(qs, qe,x,l, ns, md);
    updrng(qs, qe,x,r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

void updpos(int qp, int x, int id=0,int ns=0, int ne=n-1){
    if(ns>qp || qp>ne)
        return ;
    if(ns==ne){
        tree[id]={x,x};
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    updpos(qp, x, l, ns, md);
    updpos(qp, x, r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

ll get(int qs, int qe,  int id=0, int ns=0, int ne=n-1){
    if(ns>qe ||ne<qs)
        return 0;
    if(qs<=ns && qe>=ne){
        return tree[id].sum;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs, qe, l, ns, md)+get(qs, qe, r, md+1, ne);

}

int q,l,r;
int v;
int ty;
int t;

int main(){
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    build();

    while(q--){
        scanf("%d",&ty);
        switch(ty){
        case 1 :
            scanf("%d%d",&l,&r);
            printf("%lld\n", get(--l,--r));
            break;
        case 2 :
            scanf("%d%d%d",&l,&r,&v);
            updrng(--l, --r, v);
            break;
        case 3 :
            scanf("%d%d",&l,&v);
            updpos(--l, v);
            break;
        }
    }
    return 0;
}

