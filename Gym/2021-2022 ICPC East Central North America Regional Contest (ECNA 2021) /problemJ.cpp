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

struct DSUArray {
    vector<int> id, l, r, sz;
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
    }
} dsu;

int n;
int a[N];
bool ok[N];
map<int, vector<int> > pos;
void test_case() {
    cin >> n;
    dsu.init(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[-a[i]].pb(i);
    }
    int s, e, r;
    ll ans = 0;
    for (auto &u : pos) {
        for (auto &i : u.se) {
            ok[i] = 1;
            if (ok[i - 1]) {
                dsu.uni(i, i - 1);
            }
            if (ok[i + 1]) {
                dsu.uni(i, i + 1);
            }
            int idi = dsu.getid(i);
            ll total = -u.fi * 1ll * (dsu.sz[idi]);
            if (total > ans) {
                ans = total;
                s = dsu.l[idi] + 1;
                e = dsu.r[idi] + 1;
            } else if (total == ans && dsu.l[idi] + 1 < s) {
                s = dsu.l[idi] + 1;
                e = dsu.r[idi] + 1;
            }
        }
    }
    cout << s << " " << e << " " << ans << endl;
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
