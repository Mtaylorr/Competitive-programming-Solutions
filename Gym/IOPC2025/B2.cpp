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

int n, x[N][2], y[N][2];

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

bool intersect(int a, int b, int c, int d) { return !(b < c || a > d); }

void test_case() {
    cin >> n;
    dsu.init(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> x[i][0] >> y[i][0] >> x[i][1] >> y[i][1];
    }
    vector<vector<int> > v;
    for (int i = 0; i < n; i++) {
        v.push_back({x[i][0], x[i][1], i});
    }
    sort(all(v));
    multiset<pair<int, int> > st;
    for (auto &u : v) {
        while (st.size() && (*st.begin()).fi < u[0]) {
            st.erase(st.begin());
        }
        if (st.size()) {
            ans++;
            dsu.uni((*st.begin()).se, u[2]);
        };
        st.insert({u[1], u[2]});
    }
    v.clear();
    for (int i = 0; i < n; i++) {
        v.push_back({y[i][0], y[i][1], i});
    }
    sort(all(v));
    st.clear();
    for (auto &u : v) {
        while (st.size() && (*st.begin()).fi < u[0]) {
            st.erase(st.begin());
        }
        if (st.size()) {
            ans++;
            dsu.uni((*st.begin()).se, u[2]);
        }

        st.insert({u[1], u[2]});
    }
    int nb = 0;
    for (int i = 0; i < n; i++) {
        nb += dsu.getid(i) == i;
    }
    ans += 2 * (nb - 1);
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
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
