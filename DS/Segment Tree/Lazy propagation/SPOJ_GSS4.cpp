//https://www.spoj.com/problems/GSS4/en/
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 2 ;

typedef long long ll;


struct node{
    ll sum,mx;
    node(){
        sum=0;
        mx=0;
    }
    node(ll s, ll m){
        sum=s;
        mx=m;
    }
};

node tree[4*N];

int n, q;
int ty,x,y;
ll a[N];

node mrg(node& x, node & y){
    ll z = max(x.mx, y.mx);
    return node(x.sum+y.sum, z);
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]={a[ns],a[ns]};
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);

}

void upd(int qs, int qe ,int id=0, int ns=0, int ne=n-1){
    if(ns>qe || ne<qs){
        return;
    }
    if(tree[id].mx==1)
        return ;
    if(ns==ne){
        ll newv = sqrt(tree[id].sum);
        tree[id]=node(newv, newv);
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, l , ns, md);
    upd(qs, qe, r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);
}

ll get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || ne<qs){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return tree[id].sum;
    }

    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs, qe,  l , ns, md)+ get(qs, qe, r, md+1, ne);
}

int t;

int main()
{
    int tst=0;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            scanf("%lld",&a[i]);
        }
        build();
        printf("Case #%d:\n",++tst);
        scanf("%d",&q);
        while(q--){
            scanf("%d%d%d",&ty, &x,&y);
            if(x>y)
                swap(x,y);
            if(ty){
                printf("%lld\n", get(--x, --y));
            }else{
                upd(--x,--y);
            }
        }
        printf("\n");
    }
    return 0;
}
