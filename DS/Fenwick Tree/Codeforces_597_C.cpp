//https://codeforces.com/problemset/problem/597/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5 + 5;

int  n,k;
ll tree[N][15];
ll ans;
int a[N];

void upd(int x, int bit , ll val){
    for(;x<=n;x+=(x)&(-x)){
        tree[x][bit]+=val;
    }
}

ll get(int x, int bit){
    ll res=0;
    for(;x;x-=(x)&(-x)){
        res+=tree[x][bit];
    }
    return res;

}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=2;j<=k+1;j++){
            ll cur = get(a[i]-1,j-1);
            upd(a[i], j, cur);
        }
        upd(a[i], 1, 1);
    }
    printf("%lld\n", get(n, k+1));

    return 0;
}
