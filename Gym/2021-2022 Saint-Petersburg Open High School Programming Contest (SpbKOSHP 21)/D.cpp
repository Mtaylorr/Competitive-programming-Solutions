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

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    int greaterThanOrEqual(ll x) {
        return (lower_bound(all(values), x) - values.begin());
    }
    ll decompress(int p) { return values[p]; }
} compressor;

int n, m;
vector<int> adj[N];
int x;
int vis[N][33];
int a[N];
void dfs(int u, int r) {
    if (vis[u][r]) return;
    vis[u][r] = 1;
    if (r == 0) return;
    int val = compressor.decompress(r);
    for (auto v : adj[u]) {
        if (a[v] >= val) {
            dfs(v, r - 1);
        } else {
            dfs(v, r);
        }
    }
}
void test_case() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    cin >> x;
    compressor.init();
    int y = x;
    compressor.add(0);
    while (y) {
        compressor.add(y);
        y /= 2;
    }
    compressor.run();
    adj[0].pb(1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dfs(0, compressor.compress(x));
    int ans = 0;
    for (int i = 0; i < 33; i++) {
        if (vis[n][i]) {
            ans = max(ans, (int)compressor.decompress(i));
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
