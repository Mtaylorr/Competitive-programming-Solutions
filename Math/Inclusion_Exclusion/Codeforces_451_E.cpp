//https://codeforces.com/contest/451/problem/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;


int n;
ll s;
ll f[N];
ll dp[N];
ll invt[N];
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
ll  inv(ll u,ll mod=MOD){
    if(invt[u]!=-1)
        return invt[u];
    return invt[u]=powe(u,mod-2,mod);
}

ll cnk(ll n, ll k){
    if(k==0)
        return 1;
    ll ans=1;

    for(ll i=n+k-1;i>n;i--){
        ans=mul(ans, i);
    }
    for(ll i=1;i<=k-1;i++){
        ans=mul(ans, inv(i));
    }
    return ans;
}


int main() {
    //freopen("input.txt", "r", stdin);
    memset(invt, -1, sizeof(invt));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s;
    for(int i=0;i<n;i++){
        cin >> f[i];
    }
    ll ans=0;
    for(int msk=0;msk<(1<<n);msk++){
        int nb=0;
        ll rem=s;
        for(int i=0;i<n;i++){
            if(msk&(1<<i)){
                nb++;
                rem-=(f[i]+1);
            }
        }

        if(rem>=0){
            if(nb%2){
                ans=sub(ans, cnk(rem,n));
            }else{
                ans=add(ans, cnk(rem,n));
            }
        }
    }
    cout << ans;


    return 0;

}
