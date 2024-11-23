// Exploring the jungle
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

const int MOD = 1e9 + 7;
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

int n, a[N], k;

int cnt[N];
unordered_map<int, vector<pair<int, int> > > m;
int pos[2005][2005];
vector<int> prefs;

void test_case() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[(a[i] + a[j]) % k].pb({i, j});
        }
    }
    prefs.pb(1);
    for (auto &u : m) {
        sort(all(u.se), [](pair<int, int> &x, pair<int, int> &y) { return a[x.fi] + a[x.se] < a[y.fi] + a[y.se]; });
        for (int i = 0; i < u.se.size();) {
            int j = i;
            ll cur = a[u.se[i].fi] + a[u.se[i].se];
            while (j < u.se.size() && a[u.se[j].fi] + a[u.se[j].se] == cur) {
                pos[u.se[j].fi][u.se[j].se] = prefs.size();
                j++;
            }
            prefs.pb((prefs.back() * 1ll * (j - i + 1)) % MOD);
            i = j;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v, --w;
        int lid = pos[u][v];
        int rid = pos[w][w];
        if (lid == rid) {
            cout << 1 << endl;
            continue;
        }

        if ((a[u] + a[v]) % k != (a[w] + a[w]) % k) {
            cout << 0 << endl;
            continue;
        }
        if (lid > rid) {
            cout << 0 << endl;
            continue;
        }
        cout << (prefs[rid - 1] * 1ll * inv(prefs[lid])) % MOD << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
