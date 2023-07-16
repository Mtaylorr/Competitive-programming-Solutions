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

int id[N];
vector<int> adj[N];
multiset<ll> st[N];
int n, a[N];
ll ans[N];

void mrg(int u, int v) {
    if (st[id[u]].size() < st[id[v]].size()) {
        swap(id[u], id[v]);
    }
    multiset<ll> tmp;
    for (auto &y : st[id[v]]) {
        ll x = (*st[id[u]].begin());
        st[id[u]].erase(st[id[u]].begin());
        tmp.insert(x + y);
    }
    for (auto y : tmp) {
        st[id[u]].insert(y);
    }

    st[id[v]].clear();
    tmp.clear();
}

void solve(int u, int p = -1) {
    id[u] = u;
    st[u].clear();
    for (auto v : adj[u]) {
        if (v == p) continue;
        solve(v, u);
        mrg(u, v);
    }
    st[id[u]].insert(-a[u]);
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans[i] = 0;
        adj[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    solve(0);
    int i = 0;
    ll cur = 0;
    for (auto u : st[id[0]]) {
        cur -= u;
        ans[i++] = cur;
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            ans[i] = max(ans[i], ans[i - 1]);
        }
        cout << ans[i] << " ";
    }
    cout << endl;
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
