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
#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJAug {
   public:
    int head[N], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E], cap[E];

    void addEdge(int a, int b, ll cs, ll cp) {
        // cs = cost
        // cp = capacity
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cap[edgcnt] = cp;
        cst[edgcnt] = cs;
        edgcnt++;
    }

    void addAug(int a, int b, ll cs, ll c, ll d = 0) {
        // cs : cost
        // c  : forward capacity
        // d  : backward capacity
        addEdge(a, b, cs, c);
        addEdge(b, a, -cs, d);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

struct Dinic {
    int work[N];
    int vis[N], vid = 0, dist[N], par[N], src, snk;

    void init(int n) {
        memset(vis, 0, n * sizeof(vis[0]));
        vid = 0;
    }
    bool bfs(ADJAug &adj) {
        queue<int> q;
        dist[src] = 0;
        vis[src] = ++vid;
        q.push(src);
        while (q.size()) {
            int u = q.front();
            q.pop();
            neig(u, v, e, adj) {
                if (!adj.cap[e] || vis[v] == vid) continue;
                dist[v] = dist[u] + 1;
                vis[v] = vid;
                q.push(v);
            }
        }
        return vis[snk] == vid;
    }

    ll dfs(int u, ADJAug &adj, ll fl = 1e18) {
        if (u == snk) return fl;

        for (int &e = work[u], v; (~e) && (v = adj.to[e], 1); e = adj.nxt[e]) {
            if (!adj.cap[e] || dist[v] != dist[u] + 1) continue;
            ll f = dfs(v, adj, min(adj.cap[e], fl));
            if (f) {
                adj.cap[e] -= f;
                adj.cap[e ^ 1] += f;
                return f;
            }
        }
        return 0;
    }

    ll run(ADJAug &adj) {
        init(adj.n);
        ll flow = 0, f = 0;
        while (bfs(adj)) {
            memcpy(work, adj.head, adj.n * sizeof(adj.head[0]));
            do {
                f = dfs(src, adj);
                flow += f;
            } while (f);
        }
        return flow;
    }
} dinic;

int G, C, T;
ll c[N], g[N], t[N];

void test_case() {
    cin >> G >> C >> T;
    adj.init(C + T + 2);
    for (int i = 0; i < C; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < G; i++) {
        cin >> g[i];
    }
    for (int i = 0; i < T; i++) {
        cin >> t[i];
    }
    ll ans = 0;
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < G; j++) {
            int x;
            cin >> x;
            c[i] -= x * g[j];
        }
        c[i] = max(c[i], 0ll);
        ans += c[i];
    }
    dinic.src = adj.n - 1;
    dinic.snk = adj.n - 2;
    for (int i = 0; i < C; i++) {
        adj.addAug(dinic.src, i, 0, c[i]);
    }
    for (int i = 0; i < T; i++) {
        adj.addAug(i + C, dinic.snk, 0, t[i]);
    }

    for (int i = 0; i < C; i++) {
        int n;
        cin >> n;
        while (n--) {
            int x;
            cin >> x;
            x--;
            adj.addAug(i, x + C, 0, 1e18);
        }
    }
    cout << ans - dinic.run(adj) << endl;
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
