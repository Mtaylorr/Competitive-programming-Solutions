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
const int N = 1e6 + 5;

const int MOD = 998244353;
template <typename T, typename U>
int mul(T u, U v, int mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}
template <typename T, typename U>
int add(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}
template <typename T, typename U>
int sub(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}
template <typename T>
int powe(T u, ll v, int mod = MOD) {
    int ans = 1;
    int acc = u % mod;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}
template <typename T>
int inv(T u, int mod = MOD) {
    return powe(u, mod - 2, mod);
}

const int B = 61;
ll base[B];

void init() { memset(base, -1, sizeof(base)); }

void insert(ll x) {
    for (int i = B - 1; i >= 0; i--) {
        ll c = (1ll << i);
        if (!(c & x)) continue;
        if (base[i] == -1) {
            base[i] = x;
            break;
        } else {
            x ^= base[i];
        }
    }
}

int k;
int n;
ll a[N];

void test_case() {
    cin >> n >> k;
    init();
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        insert(a[i]);
    }
    int nb = 0;
    for (int i = 0; i < k; i++) {
        nb += base[i] != -1;
    }
    if (nb == 0) {
        cout << 1 << " " << ((1ll << k)) % MOD << endl;
        return;
    }
    ll ans = 1;
    for (int i = 0; i < nb; i++) {
        ll x = (1ll << nb) - (1ll << i);
        x %= MOD;
        ans = (ans * x) % MOD;
        ans = (ans * inv(i + 1)) % MOD;
    }

    cout << nb << " " << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
