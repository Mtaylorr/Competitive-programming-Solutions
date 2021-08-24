//https://www.hackerrank.com/contests/epiccode/challenges/square-array/problem

#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
const int MOD = 1e9 +7;

typedef long long ll;


int mul(ll u , ll v, ll mod=MOD){
	return ((u%mod)*(v%mod))%mod;
}
int add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

int sub(ll u, ll v , ll mod=MOD){
	return ((u%mod)-(v%mod)+mod)%mod;
}

struct node{
    int ss;
    int sqs;
    int nb;
    bool upd;
    node(){
        ss=sqs=nb=0;
        upd=0;
    }
    node(int _ss, int _sqs, int _nb, bool _up){
        ss=_ss;
        sqs=_sqs;
        nb=_nb;
        upd=_up;
    }
};

node tree[4*N];
int val[4*N];
int n,q, t,l,r;
int cum_1[N];
int cum_2[N];

void unlazy(int id, int ns, int ne){
    if(!tree[id].upd)
        return ;
    int sz = (ne-ns+1);
    val[id]=add(val[id], mul(tree[id].ss,sz));
    val[id]=add(val[id], mul(tree[id].nb,cum_1[sz-1]));
    val[id]=add(val[id], mul(tree[id].sqs, sz));
    val[id]=add(val[id], 2ll*mul(cum_1[sz-1], tree[id].ss));
    val[id]=add(val[id], mul(tree[id].nb,cum_2[sz-1]));
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        int md = ns+(ne-ns)/2;
        int lsz= (md-ns+1);
        tree[l].ss=add(tree[l].ss, tree[id].ss);
        tree[l].sqs=add(tree[l].sqs,tree[id].sqs);
        tree[l].nb=add(tree[l].nb, tree[id].nb);
        tree[l].upd=1;
        int ss = add(tree[id].ss, mul(tree[id].nb, lsz));
        int sqs = tree[id].sqs;
        sqs=add(sqs,mul(tree[id].nb, mul(lsz, lsz)));
        sqs=add(sqs,mul(2*lsz, tree[id].ss));
        tree[r].ss=add(tree[r].ss, ss);
        tree[r].sqs=add(tree[r].sqs,sqs);
        tree[r].nb=add(tree[r].nb, tree[id].nb);
        tree[r].upd=1;

    }
    tree[id].ss=0;
    tree[id].sqs=0;
    tree[id].nb=0;
    tree[id].upd=0;
}

void upd(int qs , int qe, int qval  , int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns , ne);
    if(qs>ne || qe<ns){
        return ;
    }
    if(qs<=ns && qe>=ne){
        tree[id]= node(qval, mul(qval, qval),1, 1);
        unlazy(id, ns, ne);
        return ;
    }
    int l=2*id+1;
    int r =l+1;
    int md=ns+(ne-ns)/2;
    int lsz = min(md,ne)-max(ns,qs)+1;
    if(lsz<0)
        lsz=0;
    upd(qs, qe, qval, l, ns, md);
    upd(qs, qe, qval+lsz,r,md+1, ne);
    val[id] = add(val[l], val[r]);
}

int get(int qs, int qe, int id=0, int ns=0,int ne=n-1){
    unlazy(id, ns, ne);
    if(qs>ne || qe<ns)
        return 0;
    if(qs<=ns && qe>=ne){
        return val[id];
    }
    int l=2*id+1;
    int r =l+1;
    int md=ns+(ne-ns)/2;
    return add(get(qs, qe, l, ns, md), get(qs, qe, r, md+1,ne));
}




int main()
{
    for(int i=1;i<N;i++){
        cum_1[i]=add(i,cum_1[i-1]);
        cum_2[i]=add(mul(i,i), cum_2[i-1]);
    }
    scanf("%d%d",&n,&q);
    for(int i=0;i<q;i++){
        scanf("%d%d%d",&t, &l,&r);
        --l;
        --r;
        switch(t){
        case 1:
            upd(l,r,1);
            break;
        case 2:
            printf("%d\n", get(l,r));
        }
    }

    return 0;
}
