#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e5+5;
const int MOD = 1e9 +7;

int t,n,k;
ll a[N];
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("rabbits.in", "r", stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld", &a[i]);
    }
    ll res=1e18;
    sort(a,a+n);
    int sz = n/2;
    for(int i=sz-1;i<n;i++){
        res=min(res, a[i]-a[i-sz+1]);
    }
    printf("%lld",res);
    return 0;
}
