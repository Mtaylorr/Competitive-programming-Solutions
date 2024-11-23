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

int n, q;
int r[N], a[N], b[N];
int invr[N];

void test_case() {
    cin >> n >> q;
    dsu.init(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
        --r[i];
        invr[r[i]] = i;
        dsu.uni(i, r[i]);
    }
    for (int i = 0; i < q; i++) {
        cin >> a[i];
        --a[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> b[i];
        --b[i];
    }
    vector<pair<int, int> > ans;
    for (int i = 0; i < q; i++) {
        if (dsu.sameSet(a[i], b[i])) continue;
        int x = dsu.getid(a[i]);
        int y = dsu.getid(b[i]);

        int w = invr[x];
        int z = r[y];
        ans.emplace_back(y, w);
        r[y] = x;
        invr[x] = y;
        r[w] = z;
        invr[z] = w;

        dsu.uni(x,y);
    }

    cout << ans.size() << endl;
    for (auto &u : ans) {
        cout << u.fi + 1 << " " << u.se + 1 << "\n";
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
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
