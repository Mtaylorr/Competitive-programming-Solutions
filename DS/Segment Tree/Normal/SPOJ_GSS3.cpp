//https://www.spoj.com/problems/GSS3/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

typedef long long ll ;

struct node{
    ll p,s;
    ll sm,ans;
    node(){
        p=s=sm=0;
        ans=-1e18;
    }
    node(ll _ans, ll _sm, ll _p, ll _s){
       ans=_ans;
       sm=_sm;
       p=_p;
       s=_s;
    }
};

ll a[N];
int n,q,l,r,ty;
node tree[4*N];
char t;

node mrg(node &x, node& y){
    node res = node();
    res.p = max({x.p, x.sm+y.p});
    res.s = max({y.s, y.sm+x.s});
    res.sm = x.sm+y.sm;
    res.ans = max({x.ans,y.ans, x.s + y.p});

    return res;
}

void build(int id=0,int ns = 0, int ne = n-1){
    if(ns==ne){
        tree[id] = node(a[ns],a[ns], a[ns],a[ns]);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id] = mrg(tree[l],tree[r]);
}


node query(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || qs>ne){
        return node(-1e18,0,-1e18,-1e18);
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    node ndl = query(qs, qe, l, ns, md);
    node ndr = query(qs, qe,r, md+1,ne);
    return mrg(ndl,ndr );
}


void upd(int pos,ll val, int id=0, int ns=0,int ne=n-1){
    if(ns>pos || pos>ne){
        return;
    }
    if(ns==ne){
        tree[id]=node(val,val, val, val);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(pos, val,l, ns, md);
    upd(pos, val,r, md+1, ne);
    tree[id] = mrg(tree[l],tree[r]);
}


int x;
int main()
{
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%lld",&a[i]);
    }
    scanf("%d",&q);
    build();
    for(int i=0;i<q;i++){
        scanf("%d%d%d",&ty,&l,&r);
        if(ty)
            printf("%lld\n",query(--l,--r).ans);
        else
            upd(--l,r);
    }


    return 0;
}
