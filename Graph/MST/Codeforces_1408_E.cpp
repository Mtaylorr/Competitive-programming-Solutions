//https://codeforces.com/problemset/problem/1408/E
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
int n, m;
int u[N], v[N], w[N];
int a[N], b[N];
vector<int> edges;

void test_case() {
    cin >> m >> n;
    dsu.init(n + m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int c = 0;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            x--;
            u[c] = i;
            v[c] = x + m;
            w[c] = a[i] + b[x];
            edges.pb(c);
            c++;
        }
    }
    sort(all(edges), [](int &a, int &b) { return w[a] > w[b]; });
    ll ans = 0;
    for (auto i : edges) {
        if (dsu.sameSet(u[i], v[i])) {
            ans += w[i];
        } else {
            dsu.uni(u[i], v[i]);
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
