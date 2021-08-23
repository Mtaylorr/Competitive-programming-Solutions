https://www.spoj.com/problems/KQUERY/
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 2;

struct node{
    int sm;
    node(){
        sm=0;
    }
    node(int s){
        sm=s;

    }
};

struct Query{
    int id, l,r,k;
    Query(){
        id=l=r=k=0;
    }
    Query(int i, int _l, int _r, int _k){
        id=i;
        l=_l,r=_r;
        k=_k;
    }
};

int ans[N];
int n,q,l,r,k;
node tree[4*N];
char t;

node mrg(node &x, node& y){
    return node(x.sm+y.sm);
}


node query(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || qs>ne){
        return node(0);
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

void upd(int pos, int id=0, int ns=0,int ne=n-1){
    if(ns>pos || pos>ne){
        return;
    }
    if(ns==ne){
        tree[id]=node(1);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(pos, l, ns, md);
    upd(pos, r, md+1, ne);
    tree[id] = mrg(tree[l],tree[r]);
}

Query Qu[N];

bool cmp(Query& a, Query& b){
    if(a.k!=b.k)
        return a.k>b.k;
    return a.id>b.id;
}

int x;
int main()
{
    scanf("%d",&n);
    int qi=0;
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        Qu[qi++]=Query(-1,i,i,x);
    }
    cin >> q;
    for(int i=0;i<q;i++){
        cin >> l >> r >> k;
        --l,--r;
        Qu[qi++]=Query(i, l,r,k);
    }
    sort(Qu,Qu+qi,cmp);
    for(int i=0;i<qi;i++){
        if(Qu[i].id!=-1){
            ans[Qu[i].id]=query(Qu[i].l, Qu[i].r).sm;
        }else{
            upd(Qu[i].l);
        }
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << "\n";
    }
    return 0;
}
