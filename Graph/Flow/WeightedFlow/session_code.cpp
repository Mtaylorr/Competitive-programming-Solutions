// https://vjudge.net/problem/HDU-1532
//  Mtaylor
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

#define neig(u, v, e, adj) for (int e = adj.head[u], v; (e != -1) && (v = adj.to[e], 1); e = adj.nxt[e])

// N number of nodes
// E number of edges * 2
const int E = 1e6;
struct ADJ {
    int head[N], edgcnt, to[E], nxt[E], cap[E];
    long long cst[E];
    int n;
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
    void addEdge(int u, int v, int w, int c) {
        nxt[edgcnt] = head[u];
        to[edgcnt] = v;
        cap[edgcnt] = c;
        cst[edgcnt] = w;
        head[u] = edgcnt++;
    }
    void addAugEdge(int u, int v, int w, int c, int d = 0) {
        addEdge(u, v, w, c);
        addEdge(v, u, -w, d);
    }
} adj;

struct MinCostMaxFlow {
    int snk;
    vector<int> vis;
    vector<int> par;
    vector<long long> dist;
    vector<int> fl;
    int vid = 0;

    int bellmanFord(int src, ADJ &adj) {
        vid++;
        fill(all(dist), 1e18);
        fill(all(fl), 0);
        queue<int> q;
        q.push(src);
        vis[src] = vid;
        dist[src] = 0;
        fl[src] = INT_MAX;
        while (!q.empty()) {
            int s = q.size();
            while (s--) {
                int u = q.front();
                q.pop();
                vis[u] = 0;
                neig(u, v, e, adj) {
                    if (adj.cap[e] == 0) continue;
                    long long nd = dist[u] + adj.cst[e];
                    if (nd < dist[v]) {
                        fl[v] = min(fl[u], adj.cap[e]);
                        dist[v] = nd;
                        par[v] = e;
                        if (vis[v] != vid) {
                            vis[v] = vid;
                            q.push(v);
                        }
                    }
                }
            }
        }
        return fl[snk];
    }

    pair<long long, long long> run(ADJ &adj, int src, int _snk) {
        snk = _snk;
        long long maxFlow = 0;
        long long flow = 0;
        long long cost = 0;
        vis.assign(adj.n, 0);
        dist.resize(adj.n);
        par.resize(adj.n);
        fl.resize(adj.n);
        while (flow = bellmanFord(src, adj)) {
            cost += flow * dist[snk];
            maxFlow += flow;
            int u = snk;
            while (u != src) {
                int e = par[u];
                adj.cap[e] -= flow;
                adj.cap[e ^ 1] += flow;
                u = adj.to[e ^ 1];
            }
        }
        return {cost, maxFlow};
    }
} mcmf;

int n, m;
int g[55][55];
int a[55], b[55];
void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> g[i][j];
    }
    int sma = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sma += a[i];
    }
    int smb = 0;
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        smb += b[i];
    }
    if (sma != smb) {
        cout << -1 << endl;
        return;
    }
    adj.init(n * m + n + m + 2);
    int src = adj.n - 1;
    int snk = adj.n - 2;
    for (int i = 0; i < n; i++) {
        adj.addAugEdge(src, n * m + i, 0, a[i]);
    }
    for (int i = 0; i < m; i++) {
        adj.addAugEdge(n * m + n + i, snk, 0, b[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int id = i * m + j;
            adj.addAugEdge(id, n * m + n + j, 0, 1);
            adj.addAugEdge(n * m + i, id, 1 - g[i][j], 1);
        }
    }
    pair<ll, ll> rs = mcmf.run(adj, src, snk);
    if (rs.second != smb) {
        cout << -1 << endl;
        return;
    }
    ll ans = rs.first;
    for (int i = 0; i < n; i++) {
        int u = n * m + i;
        neig(u, v, e, adj) {
            if (v >= 0 && v < n * m) {
                if (adj.cap[e] == 1 && adj.cst[e] == 0) {
                    ans++;
                }
            }
        }
    }

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
    while (T--) {
        test_case();
    }
    return 0;
}
