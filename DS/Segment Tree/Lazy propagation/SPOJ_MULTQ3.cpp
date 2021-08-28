//https://www.spoj.com/problems/MULTQ3/
#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;

typedef long long ll;

int n,q;
int a,b;
int ty;


struct node{
    int v[3];
    node(){
        memset(v,0,sizeof(v));
    }
    node(int x, int y, int z){
        v[0]=x;
        v[1]=y;
        v[2]=z;
    }
};

node tree[4*N];
int lazy[4*N];



node mrg(node &a, node & b){
    return node(a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2]);
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id].v[0]=1;
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
    int v[3];
    for(int i=0;i<3;i++){
        v[i]=tree[id].v[(i-lazy[id]+3)%3];
    }
    for(int i=0;i<3;i++){
        tree[id].v[i]=v[i];
    }
    if(ns!=ne){
        int l=2*id+1;
        int r = l+1;
        lazy[l]+=lazy[id];
        lazy[l]%=3;
        lazy[r]+=lazy[id];
        lazy[r]%=3;
    }
    lazy[id]=0;
}



void upd(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return ;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]+=1;
        lazy[id]%=3;
        unlazy(id, ns, ne);
        return ;
    }

    int l=2*id+1;
    int r = l+1;
    int md=ns+(ne-ns)/2;
    upd(qs, qe, l, ns, md);
    upd(qs, qe, r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);
}

int get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return tree[id].v[0];
    }
    int l=2*id+1;
    int r = l+1;
    int md=ns+(ne-ns)/2;
    return get(qs, qe, l, ns, md)+get(qs, qe, r, md+1, ne);
}

int main(){
    scanf("%d%d",&n,&q);
    build();
    while(q--){
        scanf("%d%d%d",&ty, &a, &b);
        if(ty){
            printf("%d\n", get(a, b));
        }else{
            upd(a, b);
        }
    }

    return 0;
}

