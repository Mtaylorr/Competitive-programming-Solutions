//https://www.spoj.com/problems/FREQUENT/
#include <iostream>

using namespace std;

const int N = 1e5 + 2;

struct node{
    int lv,rv;
    int lf, rf;
    int f;
    node(){
        lv=rv=lf=rf=f=0;
    }
    node(int _f, int _lv, int _lf, int _rv, int _rf){
       f=_f;
       lv=_lv, lf=_lf;
       rv=_rv, rf=_rf;
    }
};

int a[N];
int n,q,l,r;
node tree[4*N];
char t;

node mrg(node &x, node& y){
    if(x.lv<-1e6)
        return node(y);
    if(y.lv<-1e6)
        return node(x);
    node res = node();
    res.f = max(x.f,y.f);
    if(x.rv==y.lv)
        res.f=max(res.f, x.rf+y.lf);
    res.rv = y.rv;
    res.rf = y.rf;
    if(y.rv==x.rv){
        res.rf = max(res.rf, y.rf+x.rf);
    }
    res.lv = x.lv;
    res.lf = x.lf;
    if(x.lv==y.lv){
        res.lf = max(res.lf, x.lf+y.lf);
    }
    return res;
}

void build(int id=0,int ns = 0, int ne = n-1){
    if(ns==ne){
        tree[id] = node(1, a[ns], 1, a[ns],1);
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
        return node(0,-1e7, 0, -1e7,0);
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
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        scanf("%d",&q);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        build();
        for(int i=0;i<q;i++){
            scanf("%d%d",&l,&r);
            printf("%d\n",query(--l,--r).f);
        }
    }

    return 0;
}
