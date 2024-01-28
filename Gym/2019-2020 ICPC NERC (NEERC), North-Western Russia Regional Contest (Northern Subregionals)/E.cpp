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

class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
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
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;
int n, m;
int c[N];
int dist[N];
int par[N];
void dfs(int u, int p = -1) {
    par[u] = p;
    neig(u, v, e, adj) {
        if (v == p) continue;
        dist[v] = dist[u] + 1;
        dfs(v, u);
    }
}
void test_case() {
    cin >> n >> m;
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    for (int i = 0; i < m; i++) {
        cin >> c[i];
        c[i]--;
    }
    if (m == 1) {
        cout << "YES\n";
        cout << c[0] + 1 << endl;
        return;
    }
    int st = c[0];
    dfs(st);
    int mxdist = 0;
    int mxv = -1;
    for (int i = 1; i < m; i++) {
        if (dist[c[i]] > mxdist) {
            mxdist = dist[c[i]];
            mxv = c[i];
        }
    }
    if (mxdist % 2) {
        cout << "NO\n";
        return;
    }
    int d = mxdist / 2;
    int center = mxv;
    while (d--) {
        center = par[center];
    }
    dist[center] = 0;
    dfs(center);
    for (int i = 0; i < m; i++) {
        if (dist[c[i]] != mxdist / 2) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    cout << center + 1 << endl;
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
