//https://www.spoj.com/problems/PRMQUER/

#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;

typedef long long ll;

bitset<10000005> bs;


void sieve(int N){
    bs.set();
    bs[0]=bs[1]=0;
    for(int i=2;i<=N;i++){
        if(!bs[i])
            continue;
        for(ll j=i*1ll*i;j<=N;j+=i){
            bs[j]=0;
        }
    }
}

int tree[4*N],lazy[4*N];
int n;
int a[N];

int mrg(int x, int y){
    return x+y;
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]=(a[ns]<=1e7 && bs[a[ns]]);
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

void unlazy(int id , int ns , int ne){
    if(lazy[id]==-1)
        return ;
    tree[id]=(ne-ns+1)*(lazy[id]<=1e7 && bs[lazy[id]]);
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        lazy[l]=lazy[id];
        lazy[r]=lazy[id];
    }else{
        a[ns]=lazy[id];
    }
    lazy[id]=-1;
}

void updrng(int qs, int qe, ll v, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(ns>qe || ne<qs)
        return ;
    if(qs<=ns && qe>=ne){
        lazy[id]=v;
        unlazy(id, ns, ne);
        return;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    updrng(qs, qe, v,l, ns, md);
    updrng(qs, qe, v,r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

void updpos(int qi, int v, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(ns>qi ||ne<qi)
        return;
    if(ns==ne){
        a[ns]+=v;
        tree[id]=(a[ns]<=1e7 && bs[a[ns]]);
        return;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    updpos(qi, v, l, ns, md);
    updpos(qi,v, r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

ll get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(ns>qe ||ne<qs)
        return 0;
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return mrg(get(qs, qe, l, ns, md),get(qs, qe, r, md+1, ne));

}

int q,l,r;
int v;
char ty;

int main(){
    memset(lazy, -1,sizeof(lazy));
    sieve(10000000);
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    build();
    while(q--){
        scanf(" %c",&ty);
        switch(ty){
        case 'A':
            scanf("%d%d",&v,&l);
            updpos(--l, v);
            break;
        case 'Q':
            scanf("%d%d",&l,&r);
            printf("%d\n", get(--l, --r));
            break;
        case 'R':
            scanf("%d%d%d",&v,&l,&r);
            updrng(--l, --r, v);
            break;
        }
    }
    return 0;
}
