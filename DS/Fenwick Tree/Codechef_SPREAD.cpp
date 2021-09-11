//https://www.codechef.com/problems/SPREAD
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 1e3;

#define fi first
#define se second

typedef long long ll;

int n,m, u,v,p;
ll c,k;
int a[N];
char ty;
ll tree[N];

void upd(int x, ll v){
    for(;x<=n;x+=(x)&(-x)){
        tree[x]+=v;
    }
}

ll get(int x){
    ll res=0;
    for(;x;x-=(x)&(-x)){
        res+=tree[x];
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d%lld",&n,&m,&c);
    while(m--){
        scanf(" %c",&ty);
        switch(ty){
        case 'Q':
            scanf("%d",&p);
            printf("%lld\n", get(p)+c);
            break;
        case 'S':
            scanf("%d%d%lld",&u,&v,&k);
            upd(u,k);
            upd(v+1, -k);
            break;
        }
    }
    return 0;
}
