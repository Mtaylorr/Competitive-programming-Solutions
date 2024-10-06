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
const int N = 5e5 + 5;

int n;
ll f[N];
vector<int> adj[N];
int bchd[N];
int ti = -1, tin[N], tout[N];
vector<int> nodes;
int dpsz[N];
ll m[N];
void dfs(int u) {
    tin[u] = ++ti;
    nodes.push_back(u);
    int bid = -1;
    int bsz = -1;
    dpsz[u] = 1;
    for (auto &v : adj[u]) {
        dfs(v);
        dpsz[u] += dpsz[v];
        if (dpsz[v] > bsz) {
            bsz = dpsz[v];
            bid = v;
        }
    }
    bchd[u] = bid;
    tout[u] = ti;
}

ll calc(int u) { return -(f[u] * (2 * m[u] - 1)); }

set<pair<ll, int>> st;
pair<ll, int> p;

void solve(int u, bool keep = 1) {
    for (auto &v : adj[u]) {
        if (v == bchd[u]) continue;
        solve(v, 0);
    }
    if (bchd[u] != -1) solve(bchd[u], 1);
    for (auto &v : adj[u]) {
        if (v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            int nd = nodes[i];
            if (m[nd]) st.insert({calc(nd), nd});
        }
    }
    m[u]++;
    while (st.size()) {
        p = *st.begin();

        ll sm = (2 * m[u] + 1) * f[u] + p.fi;
        // dbg(u, p.se, sm);
        if (sm >= 0) break;
        st.erase(st.begin());
        int v = p.se;
        m[v]--;
        if (m[v]) st.insert({calc(v), v});
        m[u]++;
    }
    st.insert({calc(u), u});
    // dbg(u, m[u]);
    if (!keep) {
        st.clear();
    }
}

void test_case() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        --p;
        adj[p].pb(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    dfs(0);
    solve(0);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        // dbg(i, m[i]);
        ans += f[i] * (m[i] * m[i]);
    }
    cout << ans << endl;
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
