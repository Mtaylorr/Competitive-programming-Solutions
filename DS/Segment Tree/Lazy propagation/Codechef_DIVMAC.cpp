//https://www.codechef.com/problems/DIVMAC
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;

typedef long long ll;

bitset<3000005> bs;
int least[int(2e6)+10];


void sieve(int N){
    bs.set();
    bs[0]=bs[1]=0;
    least[1]=1;
    for(int i=2;i<=N;i++){
        if(!bs[i])
            continue;
        least[i]=i;
        for(ll j=i*1ll*i;j<=N;j+=i){
            bs[j]=0;
            if(least[j]==0)
                least[j]=i;
            else
                least[j]=min(least[j],i);
        }
    }
}

int tree[4*N];
int n;
int a[N];

int mrg(int x, int y){
    return max(x,y);
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]=least[a[ns]];
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}


void upd(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || ne<qs)
        return ;
    if(tree[id]==1)
        return ;
    if(ns==ne){
        a[ns]/=least[a[ns]];
        tree[id]=least[a[ns]];
        return;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe,l, ns, md);
    upd(qs, qe,r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

int get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(ns>qe ||ne<qs)
        return 0;
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return mrg(get(qs, qe, l, ns, md),get(qs, qe, r, md+1, ne));

}

int q,l,r;
int v;
int ty;
int t;

int main(){
    sieve(2000002);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&q);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        build();
        for(int i=0;i<q;i++){
            scanf("%d%d%d",&ty, &l,&r);
            if(ty){
                printf("%d ", get(--l, --r));
            }else{
                upd(--l, --r);
            }
        }
        puts("");
    }
    return 0;
}

