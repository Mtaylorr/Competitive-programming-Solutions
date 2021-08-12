//https://codeforces.com/problemset/problem/1188/B
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


const int N = int(2e6) + 3;
const int MOD = int(1e9) + 7;


int n,p,k;
int a[N];
map<ll,ll> maa;

ll mul(ll u , ll v, ll mod=p){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=p){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=p){
    return ((u%mod)-(v%mod)+mod)%mod;
}

ll get(ll x){
    ll y = mul(x,x);
    y = mul(y,y);
    return sub(y, mul(k,x));
}




int main() {
    FAST;
    cin >> n >> p >> k;
    ll ans=0;
    for(int i=0;i<n;i++){
        cin >> a[i];
        ll x = get(a[i]);
        ans+=maa[x];
        maa[x]++;
    }
    cout << ans << endl;

    return 0;
}
