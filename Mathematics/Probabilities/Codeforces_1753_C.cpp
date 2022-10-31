//https://codeforces.com/problemset/problem/1753/C
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

const int MOD = 998244353;

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

int n, a[N];

void solve() {
    cin >> n;
    int zeros = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        zeros += a[i] == 0;
    }
    if (zeros == 0 || zeros == n) {
        cout << 0 << endl;
        return;
    }
    int k = 0;
    for (int i = 0; i < zeros; i++) {
        if (a[i] == 1) k++;
    }

    if (k == 0) {
        cout << 0 << endl;
        return;
    }
    int ans = 0;
    int s = ((n*1ll*(n-1))/2)%MOD;
    for (int i = k; i >= 1; i--) {
        ans = add(ans, mul(s,inv(mul(i, i))));
    }
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
