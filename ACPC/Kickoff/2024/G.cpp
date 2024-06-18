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
const int N = 1e5 + 5;

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
} dsu[1 << 10];

int u[2*N], v[2*N], w[2*N];
int n, m;
void test_case() {
    cin >> n >> m;
    for (int i = 0; i < (1 << 10); i++) {
        dsu[i].init(n);
    }
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        --u[i], --v[i];
    }
    for (int i = 0; i < (1 << 10); i++) {
        for (int j = 0; j < m; j++) {
            if ((w[j] & i) == w[j]) {
                dsu[i].uni(u[j], v[j]);
            }
        }
    }
    int q;
    cin >> q;
    int x, y;
    while (q--) {
        cin >> x >> y;
        --x, --y;
        int ans = 1e9;
        for (int i = 0; i < (1 << 10); i++) {
            if (dsu[i].sameSet(x, y)) {
                cout << i << endl;
                break;
            }
        }
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
