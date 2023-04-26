//https://codeforces.com/contest/1082/problem/G
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

const int E = 2e6 + 5;

#define neig(u, e, v) \
    for (int e = head[u], v; (~e) && (v = to[e], 1); e = nxt[e])
template <typename T>
struct Dinic {
    int head[N], nxt[E], to[E], edgcnt = 0, n, work[N];
    T cap[E];
    int vis[N], vid = 0, dist[N], par[N], src, snk;

    void addEdge(int a, int b, T c) {
        nxt[edgcnt] = head[a];
        to[edgcnt] = b;
        cap[edgcnt] = c;
        head[a] = edgcnt++;
    }

    void addAug(int a, int b, T fcp, T rcp = 0) {
        addEdge(a, b, fcp);
        addEdge(b, a, rcp);
    }

    void init() {
        memset(head, -1, n * sizeof(head[0]));
        memset(vis, 0, n * sizeof(vis[0]));
        edgcnt = 0;
        vid = 0;
    }
    bool bfs() {
        queue<int> q;
        dist[src] = 0;
        vis[src] = ++vid;
        q.push(src);
        while (q.size()) {
            int u = q.front();
            q.pop();
            neig(u, e, v) {
                if (!cap[e] || vis[v] == vid) continue;
                dist[v] = dist[u] + 1;
                vis[v] = vid;
                q.push(v);
            }
        }
        return vis[snk] == vid;
    }

    T dfs(int u, T fl = 1e18) {
        if (u == snk) return fl;

        for (int &e = work[u], v; (~e) && (v = to[e], 1); e = nxt[e]) {
            if (!cap[e] || dist[v] != dist[u] + 1) continue;
            T f = dfs(v, min(cap[e], fl));
            if (f) {
                cap[e] -= f;
                cap[e ^ 1] += f;
                return f;
            }
        }
        return 0;
    }

    T dinic() {
        T flow = 0, f = 0;
        while (bfs()) {
            memcpy(work, head, n * sizeof(head[0]));

            do {
                f = dfs(src);
                flow += f;
            } while (f > 0);
        }
        return flow;
    }
};

Dinic<ll> dinic;

int n, m, a[N];
int u, v, w;
void test_case() {
    cin >> n >> m;
    dinic.n = n + m + 2;
    dinic.src = dinic.n - 1;
    dinic.snk = dinic.n - 2;
    dinic.init();
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        // dinic.addAug(dinic.src, i, a[i]);
        dinic.addAug(i, dinic.snk, a[i]);
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        --u, --v;
        dinic.addAug(dinic.src, n + i, w);
        dinic.addAug(n + i, u, (ll)1e18);
        dinic.addAug(n + i, v, (ll)1e18);
        sum += w;
    }
    ll ans = dinic.dinic();
    cout << sum - ans;
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
