//https://codeforces.com/problemset/problem/156/C
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
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

MODDtype inv(MODDtype u, MODDtype mod = MOD) { return powe(u, mod - 2, mod); }

const int F = 1e6;
MODDtype fact[F];
MODDtype invfact[F];

void init_fact(MODDtype n, MODDtype mod = MOD) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++) fact[i] = mul(i, fact[i - 1], mod);
}

MODDtype cnk(MODDtype n, MODDtype k) {
    if (k > n) return 0;
    if (n == 0) return 1;
    MODDtype ans = mul(fact[n], invfact[k]);
    ans = mul(ans, invfact[n - k]);
    return ans;
}

void init_inv_fact(MODDtype n, MODDtype mod = MOD) {
    for (int i = 0; i <= n; i++) invfact[i] = powe(fact[i], mod - 2, mod);
}

void init(MODDtype n, MODDtype mod = MOD) {
    init_fact(n, mod);
    init_inv_fact(n, mod);
}
string s;
int n;
void solve() {
    cin >> s;
    n = sz(s);
    int sm = 0;
    for (int i = 0; i < n; i++) {
        sm += s[i] - 'a';
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        int csm = sm - 26 * i;
        if (csm < 0) break;
        int poss = cnk(n, i);
        int distrib = cnk(csm + n - 1, csm);
        if (i % 2 == 0) {
            ans = add(ans, mul(poss, distrib));
        } else {
            ans = sub(ans, mul(poss, distrib));
        }
    }
    cout << sub(ans,1)<< "\n";
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init(3000);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
