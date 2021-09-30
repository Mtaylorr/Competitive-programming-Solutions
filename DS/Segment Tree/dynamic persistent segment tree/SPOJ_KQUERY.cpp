//https://www.spoj.com/problems/KQUERY/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5 + 10;

struct node;
extern node *emp;

struct node{
    int occ;
    node *l , *r;
    node(){
        occ=0;
        l=r=this;
    }
    node(int x, node *ln =emp, node * rn =emp){
        occ=x;
        l=ln;
        r=rn;
    }
};

node* emp = new node;

node * nodes[N];
int n;
int x,q;
int l,r,k;

node * ins (node *rt, int v, int ns=0, int ne=1e9){
    if(ns>v || ne<v)
        return rt;
    if(ns==ne){
        return new node(rt->occ+1, rt->l, rt->r);
    }

    int md = ns+(ne-ns)/2;
    node *l = ins(rt->l, v, ns, md);
    node *r =ins(rt->r, v, md+1, ne);
    return new node(l->occ+r->occ, l, r);
}

int query(node *l, node* r, int k, int ns=0, int ne=1e9){
    if(l==emp && r==emp)
        return 0;
    if(ne<=k)
        return 0;
    if(ns>k)
        return r->occ-l->occ;
    int md = ns+(ne-ns)/2;
    return query(l->l, r->l, k, ns, md) + query(l->r, r->r, k, md+1, ne);
}

int main(){
    freopen("input.txt", "r", stdin);
    nodes[0]=emp;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        nodes[i+1] = ins(nodes[i] , x);
    }

    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n", query(nodes[l-1],nodes[r],k));
    }
    return 0;
}

