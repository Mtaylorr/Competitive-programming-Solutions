//https://www.spoj.com/problems/DCEPC206/
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 1e3;

#define fi first
#define se second

typedef long long ll;

int t,n;
int x;
int a[N];

ll tree[N];
void upd(int x, ll v){
    if(x<=0)
        return;
    for(;x<=1e6;x+=(x)&(-x)){
        tree[x]+=v;
    }
}

ll get(int x){
    if(x<=0)
        return 0;
    ll res=0;
    for(;x;x-=(x)&(-x)){
        res+=tree[x];
    }
    return res;
}



int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        ll res=0;
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            res+=get(a[i]-1);
            upd(a[i],a[i]);
        }
        for(int i=0;i<n;i++){
            upd(a[i],-a[i]);
        }
        printf("%lld\n",res);

    }
    return 0;
}
