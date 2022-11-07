//https://codeforces.com/problemset/problem/616/E
// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;

#define MODDtype ll

const int MOD = 1e9 + 7;

MODDtype mul(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}

MODDtype add(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}

MODDtype sub(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}

MODDtype powe(MODDtype u, ll v, MODDtype mod = MOD) {
    MODDtype ans = 1;
    MODDtype acc = u;
    while (v) {
        if (v % 2)
            ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

MODDtype inv(MODDtype u, MODDtype mod = MOD) {
    return powe(u, mod - 2, mod);
}
ll n, m;
ll inv2 = inv(2);

int getsm(ll s, ll n, ll r){
    if(n==1){
        return s%MOD;
    }
    s%=MOD;
    n%=MOD;
    r%=MOD;
    if(r<0)
        r+=MOD;
    ll ans=(((s + s + r*(n-1))%MOD)*((n*inv2)%MOD) )%MOD;
    return ans;
}
void solve() {
    cin >> n >> m;
    ll cur=n;
    ll sm=0;
    ll sm2=0;
    ll e = n;
    for(ll i=1;i*i<=n;i++){
        ll st = n%i;
        ll en = (n-1)/(i+1);
        ll eneq = e;
       
        en-=((en-st)%i + i)%i;
        en=max(en, st);
        ll steq = e-(en-st)/i;
        eneq = min(eneq, m);
        if(steq<=m){
            ll y = getsm(en,(eneq-steq)+1, -i);
            sm2=add(sm2,y);
        }
        
        if(i!=n/i && i<=m){
            sm2=add(sm2,n%i);
        }
        e-=(en-st)/i +1;
    }
    if(m>n){
        sm2=add(sm2, mul(m-n,n));
    }
    cout <<sm2 << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
