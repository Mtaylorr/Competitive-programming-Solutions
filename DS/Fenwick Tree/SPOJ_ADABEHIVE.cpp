//https://www.spoj.com/problems/ADABEHIVE/
#include <bits/stdc++.h>

using namespace std;
const int N = 2005;

#define fi first
#define se second

typedef long long ll;

int n,m,q;
int a,b,c,d,p;
int x;
ll tree[N][N];
int ty;

void upd(int x,int y, int v){
    for(;x<=n;x+=(x)&(-x)){
        for(int k=y;k<=m;k+=(k)&(-k))
            tree[x][k]+=v;
    }
}

ll get(int x, int y){
    ll res=0;
    for(;x;x-=(x)&(-x)){
        for(int k=y;k;k-=(k)&(-k))
            res+=tree[x][k];
    }
    return res;
}

ll query(int a, int b, int c, int d){
    return get(c,d) +get(a-1,b-1) - get(c, b-1) - get(a-1,d);
}




int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&x);
            upd(i+1, j+1,x);
        }
    }
    while(q--){
        scanf("%d",&ty);
        switch(ty){
        case 1 :
            scanf("%d%d%d",&a,&b,&p);
            upd(a,b,p);
            break;
        case 2 :
            scanf("%d%d%d%d",&a,&b,&c,&d);
            printf("%lld\n", query(a,b,c,d));
            break;
        }
    }
    return 0;
}
