//https://www.spoj.com/problems/GSS1/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

typedef long long ll ;

struct node{
    ll p,s;
    ll sm,ans;
    node(){
        p=s=sm=0;
        ans=-1e9;
    }
    node(ll _ans, ll _sm, ll _p, ll _s){
       ans=_ans;
       sm=_sm;
       p=_p;
       s=_s;
    }
};

int a[N];
int n,q,l,r;
node tree[4*N];
char t;

node mrg(node &x, node& y){
    node res = node();
    res.ans = max({x.ans,y.ans, x.s + y.p});
    res.p = max({x.p, x.sm+y.p});
    res.s = max({y.s, y.sm+x.s});
    res.sm = x.sm+y.sm;
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
        return node(-1e9,0,-1e9,-1e9);
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



int x;
int main()
{
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&q);
    build();
    for(int i=0;i<q;i++){
        scanf("%d%d",&l,&r);
        printf("%lld\n",query(--l,--r).ans);
    }


    return 0;
}
