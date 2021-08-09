//https://codeforces.com/contest/1557/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(3e6) + 3;
const int MOD = int(1e9) + 7;


ll fact[N];
ll invfact[N];

ll mul(ll u, ll v, ll mod = MOD) {
    return ((u % mod) * (v % mod)) % mod;
}

ll add(ll u, ll v, ll mod = MOD) {
    return ((u % mod) + (v % mod) + mod) % mod;
}

ll sub(ll u, ll v, ll mod = MOD) {
    return ((u % mod) - (v % mod) + mod) % mod;
}

ll powe(ll u, ll v, ll mod = MOD) {
    ll ans = 1;
    ll acc = u;
    while (v) {
        if (v % 2) {
            ans = mul(ans, acc, mod);
        }

        acc = mul(acc, acc, mod);

        v /= 2;
    }
    return ans;
}

ll inv(ll u, ll mod = MOD) {
    return powe(u, mod - 2, mod);
}

void init_fact(ll n, ll mod = MOD) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++) {
        fact[i] = mul(i, fact[i - 1], mod);
    }
}

ll cnk(ll n, ll k) {
    if (k > n)return 0;
    if (n == 0)return 1;
    ll ans = mul(fact[n], invfact[k]);
    ans = mul(ans, invfact[n - k]);
    return ans;
}

void init_inv_fact(ll n, ll mod = MOD) {
    for (int i = 0; i <= n; i++) {
        invfact[i] = powe(fact[i], mod - 2, mod);
    }
}

void init(ll n, ll mod = MOD) {
    init_fact(n, mod);
    init_inv_fact(n, mod);
}

int t;
ll n, k;

ll getsum(ll p, ll y){
    ll ans=0;
    for(ll i=k-1;i>=0;i--){
        ll u = mul(powe(y,k-i-1), powe(p,i));
        ans=add(ans, u);
    }
    return ans;
}

int main() {
    FAST;
    init(300000);
    cin >> t;
    while (t--) {
        cin >> n >> k;
        ll res = 0;
        if(n%2==1){
            res=powe(2,n-1);
        }else{
            res=sub(powe(2,n-1),1);
        }
        if(n%2){
            res=add(res,1);
            res=powe(res,k);
        }else{
            ll z = res;
            res=powe(res,k);
            res=add(res,getsum(powe(2,n),z));
        }
        cout << res << endl;
    }
    return 0;
}
