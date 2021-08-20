//https://codeforces.com/contest/446/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define fi first
#define se second

const int N = 6e5 +2;
const int MOD = 1e9 + 9;

#define all(v) (v).begin(), (v).end()

int mul(int u , int v, int mod=MOD){
	return ((u%mod)*1LL*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
	return ((u%mod)+0LL+(v%mod)+mod)%mod;
}
void addi(int &x, int &u, int &v, int mod=MOD){
	x = ((u%mod)+0LL+(v%mod)+mod)%mod;
}
void subi(int &x, int &u, int &v, int mod=MOD){
	x = ((u%mod)+0LL+mod-(v%mod)+mod)%mod;
}
void muli(int &x, int &u, int &v, int mod=MOD){
	x = ((u%mod)*1LL*(v%mod))%mod;
}
int sub(int u, int v , int mod=MOD){
	return ((u%mod)+0LL-(v%mod)+mod)%mod;
}

int n,m,ty;
int a[N];
int fib[N];
int l,r,t;
int f0[2*N], f1[2*N];
int tree[2*N];




int get_nth(ll f0, ll f1, int n){
    return (f0*fib[n]+f1*fib[n+1])%MOD;
}

void apply(int cur, int len ,int F0, int F1){
    addi(f0[cur], f0[cur], F0);
    addi(f1[cur], f1[cur], F1);
    tree[cur] = add(tree[cur], sub(get_nth(F0, F1, len+1), F1));
}


void updlazy(int id, int ns, int ne){
    if(f0[id]!=0 || f1[id]!=0){
        int sz = ne-ns+1;
        int F0 = f0[id];
        int F1 = f1[id];
        f0[id]=f1[id]=0;
        int l = 2*id+1;
        int r = l+1;
        int md = ns+(ne-ns)/2;
        apply(l, md-ns+1, F0, F1);
        int nF0 = get_nth(F0, F1, md-ns+1);
        int nF1 = get_nth(F0, F1, md-ns+2);
        F0 = nF0;
        F1 = nF1;
        apply(r, ne-md, F0,F1);
    }
}

void upd(int qs, int qe , int F0, int F1,int id=0, int ns=0, int ne=n-1){

    if(qs>ne || ns>qe)
        return ;
    if(qs<=ns && qe>=ne){
        apply(id, ne-ns+1, F0, F1);
        return ;
    }
    updlazy(id, ns, ne);
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, F0, F1, l, ns, md);
    int lsz = min(qe, md) - max(ns,qs)+1;
    if(lsz<0)
        lsz=0;
    upd(qs, qe, get_nth(F0, F1, lsz), get_nth(F0, F1,lsz+1), r, md+1, ne);
    tree[id] =add(tree[l], tree[r]);
}


int getsum(int qs, int qe, int id=0, int ns=0, int ne=n-1){

    if(qs>ne || ns>qe)
        return 0;
    if(qs<=ns && qe>=ne)
        return tree[id];
    updlazy(id, ns, ne);
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return add(getsum(qs, qe, l, ns, md), getsum(qs, qe, r, md+1, ne));
}

int getrange(int l, int r){
    if(l==0)
        return a[r];
    return sub(a[r],a[l-1]);
}

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        if(i)
            addi(a[i],a[i],a[i-1]);
    }
    fib[0] = 1;
    fib[1] = 0;
    for(int i=2;i<2*n+2;i++){
        addi(fib[i],fib[i-1],fib[i-2]);
    }
    while(m--){
       scanf("%d%d%d",&t,&l,&r);
       --l;--r;
        if(t==1){
            upd(l,r,1,1);
        }else{
            printf("%d\n",add(getsum(l,r),getrange(l,r)));
        }

    }


    return 0;
}
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define fi first
#define se second

const int N = 6e5 +2;
const int MOD = 1e9 + 9;

#define all(v) (v).begin(), (v).end()

int mul(int u , int v, int mod=MOD){
	return ((u%mod)*1LL*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
	return ((u%mod)+0LL+(v%mod)+mod)%mod;
}
void addi(int &x, int &u, int &v, int mod=MOD){
	x = ((u%mod)+0LL+(v%mod)+mod)%mod;
}
void subi(int &x, int &u, int &v, int mod=MOD){
	x = ((u%mod)+0LL+mod-(v%mod)+mod)%mod;
}
void muli(int &x, int &u, int &v, int mod=MOD){
	x = ((u%mod)*1LL*(v%mod))%mod;
}
int sub(int u, int v , int mod=MOD){
	return ((u%mod)+0LL-(v%mod)+mod)%mod;
}

int n,m,ty;
int a[N];
int fib[N];
int l,r,t;
int f0[2*N], f1[2*N];
int tree[2*N];




int get_nth(ll f0, ll f1, int n){
    return (f0*fib[n]+f1*fib[n+1])%MOD;
}

void apply(int cur, int len ,int F0, int F1){
    addi(f0[cur], f0[cur], F0);
    addi(f1[cur], f1[cur], F1);
    tree[cur] = add(tree[cur], sub(get_nth(F0, F1, len+1), F1));
}


void updlazy(int id, int ns, int ne){
    if(f0[id]!=0 || f1[id]!=0){
        int sz = ne-ns+1;
        int F0 = f0[id];
        int F1 = f1[id];
        f0[id]=f1[id]=0;
        int l = 2*id+1;
        int r = l+1;
        int md = ns+(ne-ns)/2;
        apply(l, md-ns+1, F0, F1);
        int nF0 = get_nth(F0, F1, md-ns+1);
        int nF1 = get_nth(F0, F1, md-ns+2);
        F0 = nF0;
        F1 = nF1;
        apply(r, ne-md, F0,F1);
    }
}

void upd(int qs, int qe , int F0, int F1,int id=0, int ns=0, int ne=n-1){

    if(qs>ne || ns>qe)
        return ;
    if(qs<=ns && qe>=ne){
        apply(id, ne-ns+1, F0, F1);
        return ;
    }
    updlazy(id, ns, ne);
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, F0, F1, l, ns, md);
    int lsz = min(qe, md) - max(ns,qs)+1;
    if(lsz<0)
        lsz=0;
    upd(qs, qe, get_nth(F0, F1, lsz), get_nth(F0, F1,lsz+1), r, md+1, ne);
    tree[id] =add(tree[l], tree[r]);
}


int getsum(int qs, int qe, int id=0, int ns=0, int ne=n-1){

    if(qs>ne || ns>qe)
        return 0;
    if(qs<=ns && qe>=ne)
        return tree[id];
    updlazy(id, ns, ne);
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return add(getsum(qs, qe, l, ns, md), getsum(qs, qe, r, md+1, ne));
}

int getrange(int l, int r){
    if(l==0)
        return a[r];
    return sub(a[r],a[l-1]);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        if(i)
            addi(a[i],a[i],a[i-1]);
    }
    fib[0] = 1;
    fib[1] = 0;
    for(int i=2;i<2*n+2;i++){
        addi(fib[i],fib[i-1],fib[i-2]);
    }
    while(m--){
       scanf("%d%d%d",&t,&l,&r);
       --l;--r;
        if(t==1){
            upd(l,r,1,1);
        }else{
            printf("%d\n",add(getsum(l,r),getrange(l,r)));
        }

    }


    return 0;
}
