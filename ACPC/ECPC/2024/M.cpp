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

set<ll> st;
int n;
ll a[N];
ll x[N];
int q;
unordered_map<ll, vector<int> > qu, add;

struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;

ll res[N];

void test_case() {
    qu.clear();
    add.clear();
    cin >> n >> q;
    dsu.init(n);
    st.clear();
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        ll d = a[i] - a[i + 1];
        st.insert(d);
        add[d].pb(i);
    }
    for (int i = 0; i < q; i++) {
        cin >> x[i];
        st.insert(x[i]);
        qu[x[i]].pb(i);
    }
    ll ans = 0;
    for (auto &u : st) {
        for (auto &x : add[u]) {
            ans += dsu.sz[dsu.getid(x)] * 1ll * dsu.sz[dsu.getid(x + 1)];
            dsu.uni(x, x + 1);
        }
        for (auto &x : qu[u]) {
            res[x] = ans;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
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
