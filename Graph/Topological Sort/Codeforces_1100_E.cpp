//https://codeforces.com/problemset/problem/1100/E
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

const int E = 1e6 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

struct ADJ {
    int head[E], to[E], nxt[E], edgcnt = 0;
    ll cst[E];

    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }

    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int n) {
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

int n, m;
int u[N], v[N], c[N];
bool reversed[N];
int pos[N];
int vis[N];
vector<int> ord;
bool cycle;

void dfs(int u, int k) {
    vis[u] = 1;
    neig(u, v, e, adj) {
        if (adj.cst[e] <= k) continue;
        if (vis[v] == 1) {
            cycle = true;
            continue;
        } else if (vis[v] == 2) {
            continue;
        }
        dfs(v, k);
    }
    ord.pb(u);

    vis[u] = 2;
}
bool ok(int u) {
    memset(vis, 0, sizeof(vis));
    ord.clear();
    cycle = false;
    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) dfs(i, u);
    }

    if (cycle) return 0;
    reverse(ord.begin(), ord.end());
    for (int i = 0; i < n; i++) {
        pos[ord[i]] = i;
    }
    return 1;
}
void solve() {
    cin >> n >> m;
    adj.init(n);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> c[i];
        --u[i], --v[i];

        adj.addEdge(u[i], v[i], c[i]);
    }
    int l = 0;
    int r = 1e9;
    while (l < r) {
        int md = (l + r) / 2;
        if (ok(md)) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    ok(l);
    int nb = 0;
    for (int i = 0; i < m; i++) {
        if (c[i] <= l && pos[u[i]] > pos[v[i]]) {
            nb++;
            reversed[i] = 1;
        }
    }
    cout << l << " " << nb << endl;
    for (int i = 0; i < m; i++) {
        if (reversed[i]) {
            cout << i + 1 << " ";
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
