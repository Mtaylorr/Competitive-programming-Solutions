//https://www.spoj.com/problems/ANDROUND/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

typedef long long ll ;

struct node{
    ll v;
    node(){
        v=0;
    }
    node(ll _v){
       v=_v;
    }
};

int a[N];
int n,q,l,r;
node tree[4*N];
char t;

node mrg(node &x, node& y){
    return node(x.v&y.v);
}

void build(int id=0,int ns = 0, int ne = n-1){
    if(ns==ne){
        tree[id] = node(a[ns]);
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
        return node((1ll<<40)-1);
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
int k;
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        build();
        for(int i=0;i<n;i++){
            if(2*k+1>=n){
                printf("%lld ",tree[0].v);
            }else{
                if(i-k<0){
                    ll res = query(0,i+k).v;
                    res&=query(n-(abs(i-k)),n-1).v;
                    printf("%lld ", res);
                }else if(i+k>=n){
                    ll res = query(i-k,n-1).v;
                    res&=query(0,(abs(i+k-n+1))-1).v;
                    printf("%lld ", res);
                }else{
                    printf("%lld ", query(i-k, i+k).v);
                }

            }

        }
        printf("\n");
    }

    return 0;
}
