//https://www.spoj.com/problems/SEGSQRSS/
#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;

typedef long long ll;

int n,q,t;
int x,y,v;
int ty;
int a[N];
ll val[N];

struct node{
    ll sum, sqsum;
    node(){
        sum=sqsum=0;
    }
    node(ll x, ll y){
        sum=x;
        sqsum=y;
    }
};

node tree[4*N];
ll addlazy[4*N];
int setlazy[4*N];



node mrg(node &a, node & b){
    return node(a.sum+b.sum, a.sqsum+b.sqsum);
}

void build(int id=0, int ns=0, int ne=n-1){
    addlazy[id]=0;
    setlazy[id]=-1;
    if(ns==ne){
        tree[id]=node(a[ns], a[ns]*a[ns]);
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md=ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);

}

void unlazy(int id, int ns , int ne){

    if(setlazy[id]!=-1){
        tree[id].sum = val[setlazy[id]] * (ne-ns+1);
        tree[id].sqsum = val[setlazy[id]]*val[setlazy[id]]*(ne-ns+1);
    }
    tree[id].sqsum += tree[id].sum*addlazy[id] *2 + addlazy[id]*addlazy[id]*(ne-ns+1);
    tree[id].sum += addlazy[id] * (ne-ns+1);
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        if(setlazy[id]!=-1){
            setlazy[l] = setlazy[id];
            setlazy[r] = setlazy[r]=0;
            addlazy[l]=addlazy[r]=0;
        }
        addlazy[l]+=addlazy[id];
        addlazy[r]+=addlazy[id];
    }
    setlazy[id]=-1;
    addlazy[id]=0;
}



void upd(int qs, int qe,ll v,  int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return ;
    }
    if(qs<=ns && qe>=ne){
        addlazy[id]+=v;
        unlazy(id, ns, ne);
        return ;
    }

    int l=2*id+1;
    int r = l+1;
    int md=ns+(ne-ns)/2;
    upd(qs, qe,v, l, ns, md);
    upd(qs, qe,v,r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);
}

void setv(int qs, int qe,ll v,  int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return ;
    }
    if(qs<=ns && qe>=ne){
        setlazy[id]=v;
        addlazy[id]=0;
        unlazy(id, ns, ne);
        return ;
    }

    int l=2*id+1;
    int r = l+1;
    int md=ns+(ne-ns)/2;
    setv(qs, qe,v, l, ns, md);
    setv(qs, qe,v, r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);
}

ll get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return tree[id].sqsum;
    }
    int l=2*id+1;
    int r = l+1;
    int md=ns+(ne-ns)/2;
    return get(qs, qe, l, ns, md)+get(qs, qe, r, md+1, ne);
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    int tst=0;
    while(t--){
        scanf("%d%d",&n,&q);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        build();
        int qt=-1;
        printf("Case %d:\n",++tst);
        while(q--){
            scanf("%d",&ty);
            switch(ty){
            case 2 :
                scanf("%d%d",&x,&y);
                printf("%lld\n", get(--x,--y));
                break;
            case 1 :
                scanf("%d%d%d",&x,&y,&v);
                upd(--x,--y,v);
                break;
            case 0 :
                scanf("%d%d%d",&x,&y,&v);
                val[++qt]=v;
                setv(--x,--y, qt);
                break;
            }
        }
    }

    return 0;
}
