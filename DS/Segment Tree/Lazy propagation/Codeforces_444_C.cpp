//https://codeforces.com/contest/444/problem/C
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;

const int N = int(1e6)+5;

int n,m;
ll lazy[N];
ll tree[N];
ll col[N];

int ty,l,r,x;

void updlazy(int id , ll ns, ll ne){
    if(lazy[id]==0)
        return ;

    tree[id] += lazy[id]*(ne-ns+1);
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        lazy[l]+=lazy[id];
        lazy[r]+=lazy[id];
        col[l]=col[r]=col[id];
    }
    lazy[id]=0;
}

void build(int id=0, int ns=0,int ne=n-1){
    if(ns==ne){
        tree[id]=0;
        col[id] = ns+1;
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns + (ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=tree[l]+tree[r];
    if(col[l]==col[r]){
        col[id]=col[l];
    }else{
        col[id]=-1;
    }
 }

 void upd(int qs, int qe, ll v, int id=0, int ns=0, int ne=n-1){
     updlazy(id, ns, ne);
     if(qs>ne || qe<ns){
        return ;
     }
    if(qs<=ns && qe>=ne && col[id]!=-1){
        lazy[id]+=abs(col[id]-v);
        col[id] = v;
        updlazy(id, ns, ne);

        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns + (ne-ns)/2;
    upd(qs, qe, v,l, ns,  md);
    upd(qs, qe, v,r, md+1, ne);
    tree[id]=tree[l]+tree[r];
    if(col[l]==col[r]){
        col[id]=col[l];
    }else{
        col[id]=-1;
    }
 }

 ll get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    updlazy(id, ns, ne);
    if(qs>ne || qe<ns)
        return 0;
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns + (ne-ns)/2;
    ll v1 = get(qs, qe, l, ns, md);
    ll v2 = get(qs, qe, r, md+1,ne);
    return v1+v2;
 }

int main(){
    scanf("%d%d",&n,&m);
    build();
    for(int i=0;i<m;i++){
        scanf("%d",&ty);
        if(ty==1){
            scanf("%d%d%d",&l,&r,&x);
            l--;r--;
            upd(l,r,x);
        }else{
            scanf("%d%d",&l,&r);
            l--;r--;
            printf("%lld\n",get(l,r));
        }
    }
    return 0;
}
