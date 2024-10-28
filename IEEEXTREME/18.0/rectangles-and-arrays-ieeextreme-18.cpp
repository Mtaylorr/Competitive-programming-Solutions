//https://csacademy.com/ieeextreme18/task/rectangles-and-arrays-ieeextreme-18/
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

int n;
int x;
int a[N];

struct DSUArray {
    vector<int> id, l, r, sz;
    vector<int> mn;
    void init(int n) {
        id.assign(n, 0);
        l.assign(n, 0);
        r.assign(n, 0);
        sz.assign(n, 0);
        mn.resize(n);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            l[i] = i;
            r[i] = i;
            sz[i] = 1;
            mn[i] = a[i];
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
        sz[v] += sz[u];
        mn[v] = min(mn[v], mn[u]);
    }
} dsu;

vector<int> pos[N];
void test_case() {
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].pb(i);
    }
    dsu.init(n);
    ll ans = 0;
    for (int i = 1e6; i >= 0; i--) {
        for (auto &p : pos[i]) {
            int lf = 0;
            int rg = 0;
            int mn = x;

            if (p - 1 >= 0 && a[p - 1] > a[p]) {
                lf = dsu.sz[dsu.getid(p - 1)];
                mn = min(mn, dsu.mn[dsu.getid(p - 1)]);
            }
            if (p + 1 < n && a[p + 1] > a[p]) {
                rg = dsu.sz[dsu.getid(p + 1)];
                mn = min(mn, dsu.mn[dsu.getid(p + 1)]);
            }
            int ln = lf + rg + 1;
            ans = max(ans, (ln * 1ll * mn));
        }
        for (auto &p : pos[i]) {
            int lf = 0;
            int rg = 0;
            int mn = x;

            if (p - 1 >= 0 && a[p - 1] >= a[p]) {
                dsu.uni(p, p - 1);
            }
            if (p + 1 < n && a[p + 1] >= a[p]) {
                dsu.uni(p, p + 1);
            }
            ans = max(ans, (dsu.sz[dsu.getid(p)] * 1ll * i));
        }
    }
    cout <<ans;
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
