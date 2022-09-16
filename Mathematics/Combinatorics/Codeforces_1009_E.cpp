//https://codeforces.com/problemset/problem/1009/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 5, M=1000 +5,E = 2000 +5;
const int MOD = 998244353 ;

int a[N];
int n;

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
    ll ans=1;
    ll acc=u;
    while(v){
        if(v%2){
            ans=mul(ans,acc,mod);
        }
        acc = mul(acc,acc,mod);
        v/=2;
    }
    return ans;
}
int po[N];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    ll sm=0;
    ll ans=0;
    for(int i=0;i<n;i++){
        cin >> a[i];
        int x = mul(a[i], powe(2, n-1-i-1));
        int y = mul(a[i], powe(2, n-1-i));
        ans=add(ans, add(sm,y));
        sm=add(sm, x);
    }
    cout << ans << endl;
    return 0;


}
