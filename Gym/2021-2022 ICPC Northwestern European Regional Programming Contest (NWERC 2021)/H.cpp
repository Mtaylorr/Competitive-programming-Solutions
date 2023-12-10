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

ll s[N];
struct DSUArray {
    vector<int> id, l, r, sz;
    ll sm[N];
    void init(int n) {
        id.assign(n, 0);
        l.assign(n, 0);
        r.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            l[i] = i;
            r[i] = i;
            sz[i] = 1;
            sm[i] = s[i];
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        l[v] = min(l[v], l[u]);
        r[v] = max(r[v], r[u]);
        sm[v] += sm[u];
        sz[v] += sz[u];
    }
} dsu;

int n;

map<ll, vector<int> > pos;
map<ll, vector<tuple<ll, int, int> > > nxt;
ll dp[N];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        s[i + n] = s[i];
        pos[s[i]].pb(i);
        pos[s[i]].pb(i + n);
        dp[i] = 1e18;
        dp[i + n] = 1e18;
    }
    dsu.init(2 * n);
    ll ans = 1e18;
    for (auto &u : pos) {
        for (auto &v : u.se) {
            int r = (v + 1);
            int l = (v - 1);
            if (l >= 0 && s[l] <= s[v]) {
                dsu.uni(v, l);
            }
            if (r < 2 * n && s[r] <= s[v]) {
                dsu.uni(v, r);
            }
        }
        for (auto &v : u.se) {
            int id = dsu.getid(v);
            // dbg(v, s[v], dsu.sz[id]);
            if (dsu.sz[id] >= n) {
                dp[v] = 0;
                ans = min(ans, u.fi);
            } else {
                int r = (dsu.r[id] + 1);
                int l = (dsu.l[id] - 1);
                if (r < 2 * n)
                    nxt[-u.fi].pb({dsu.sm[id], v, r});
                if (l >= 0)
                    nxt[-u.fi].pb({dsu.sm[id], v, l});
            }
        }
    }

    for (auto &u : nxt) {
        // dbg(u.fi);
        for (auto &v : u.se) {
            ll sm = get<0>(v);
            int p = get<1>(v);
            int nx = get<2>(v);
            dp[p] = min(dp[p], max({0ll, s[nx] - sm, dp[nx]}));
            ans = min(ans, max(dp[p], s[p]));
            // dbg(p, nx, sm, dp[p], s[p], s[nx], ans, dp[nx]);
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
