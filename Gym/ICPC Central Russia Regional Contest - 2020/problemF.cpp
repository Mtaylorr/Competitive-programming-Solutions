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

map<int, int> dist[10004];
set<pair<int, int>> vis;
int X, Y;
int s, t;
int x[N], y[N];
int n, m;

int calc_dist(int u, int v) {
    ll dx = (x[u] - x[v]);
    ll dy = (y[u] - y[v]);
    return (int)floor(sqrt(dx * dx + dy * dy));
}

bool ok(int w, int u, int v) {
    if (w == -1) return 1;
    if (w == v) return 1;
    ll dx1 = x[w] - x[u];
    ll dy1 = y[w] - y[u];
    ll dx2 = x[v] - x[u];
    ll dy2 = y[v] - y[u];
    ll d1 = dx1 * dx1 + dy1 * dy1;
    ll d2 = dx2 * dx2 + dy2 * dy2;

    ll dot_product = dx1 * dx2 + dy1 * dy2;
    //dbg(w, u, v, acos(dot_product * 1.0 / (sqrt(d1) * sqrt(d2))));
    ll dot = dot_product * dot_product;
    //dbg(dot_product, d1, d2, dx1, dy1, dx2, dy2);
    return 4 * dot >= d1 * d2 && dot_product < 0;
}

void dijk(int src) {
    for (int i = 0; i <= n + 1; i++) {
        dist[i].clear();
    }
    dist[src][-1] = 1e9;
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({(int)1e9, {src, -1}});
    pair<int, pair<int, int>> p;
    while (!pq.empty()) {
        p = pq.top();
        pq.pop();
        int d = p.fi;
        int u = p.se.fi;
        int w = p.se.se;
        //dbg(u, w, d);
        if (vis.count({u, w})) continue;
        vis.insert({u, w});
        neig(u, v, e, adj) {
            //dbg(w, u, v, ok(w, u, v));
            if (!ok(w, u, v)) continue;
            if (vis.count({v, u})) continue;
            int nd = min(d, calc_dist(u, v));
            if (dist[v][u] < nd) {
                dist[v][u] = nd;
                pq.push({nd, {v, u}});
            }
        }
    }
}

void test_case() {
    cin >> X >> Y;
    cin >> s >> t;
    cin >> n >> m;
    adj.init(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    x[0] = s;
    y[0] = 0;
    x[n + 1] = t;
    y[n + 1] = Y;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj.addBiEdge(u, v);
    }
    dijk(0);
    int rs = 0;
    for (auto &u : dist[n + 1]) {
        rs = max(rs, u.se);
    }
    dijk(n + 1);
    for (auto &u : dist[0]) {
        rs = max(rs, u.se);
    }
    cout << rs << endl;
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
