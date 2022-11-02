//https://codeforces.com/contest/340/problem/E
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

#define MODDtype int

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
const int F = 1e6;
MODDtype fact[F];
MODDtype invfact[F];

void init_fact(MODDtype n, MODDtype mod = MOD) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++)
        fact[i] = mul(i, fact[i - 1], mod);
}

MODDtype cnk(MODDtype n, MODDtype k) {
    if (k > n)return 0;
    if (n == 0)return 1;
    MODDtype ans = mul(fact[n], invfact[k]);
    ans = mul(ans, invfact[n - k]);
    return ans;
}

void init_inv_fact(MODDtype n, MODDtype mod = MOD) {
    for (int i = 0; i <= n; i++)
        invfact[i] = powe(fact[i], mod - 2, mod);
}

void init(MODDtype n, MODDtype mod = MOD) {
    init_fact(n, mod);
    init_inv_fact(n, mod);
}

int n;
int a[N];
bool vis[N];
void solve() {
    init(2005);
    cin >> n;
    int places = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] != -1) vis[a[i]] = 1;
        places += (a[i] == -1);
    }
    int nb = 0;
    for (int i = 1; i <= n; i++) {
        nb += (vis[i] == 0 && a[i] == -1);
    }
    int ans=0;
    for(int i=0;i<=nb;i++){
        if(i%2==0){
            ans=add(ans, mul(cnk(nb,i), fact[places-i]));
        }else{
            ans=sub(ans, mul(cnk(nb,i), fact[places-i]));
        }
    }
    cout << ans;
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
