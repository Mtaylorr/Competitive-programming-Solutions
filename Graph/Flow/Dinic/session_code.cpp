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
    int n;
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
    void addEdge(int u, int v, int c) {
        nxt[edgcnt] = head[u];
        to[edgcnt] = v;
        cap[edgcnt] = c;
        head[u] = edgcnt++;
    }
    void addAugEdge(int u, int v, int c, int d = 0) {
        // c direct capacity
        // d indirect capcaity
        addEdge(u, v, c);  // pairs edge => other , ^=1
        addEdge(v, u, d);  // impair
    }
} adj;

struct EdmondsKarp {
    int snk;
    vector<int> vis;
    vector<int> dist;
    int tmp[E];
    int vid = 0;

    bool bfs(int src, ADJ &adj) {
        vid++;
        fill(all(dist), 0);
        queue<int> q;
        q.push(src);
        vis[src] = vid;
        dist[src] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            neig(u, v, e, adj) {
                if (adj.cap[e] == 0) continue;
                if (vis[v] == vid) continue;
                vis[v] = vid;
                q.push(v);
                dist[v] = dist[u] + 1;
            }
        }
        return vis[snk] == vid;
    }

    long long dfs(int u, int f, ADJ &adj) {
        if (u == snk) {
            return f;
        }
        for (int &e = tmp[u], v; (e != -1) && (v = adj.to[e], 1); e = adj.nxt[e]) {
            if (adj.cap[e] == 0) continue;
            if (dist[v] != dist[u] + 1) continue;
            int fl = dfs(v, min(f, adj.cap[e]), adj);
            if (fl) {
                adj.cap[e] -= fl;
                adj.cap[e ^ 1] += fl;
                return fl;
            }
        }
        return 0;
    }

    long long run(ADJ &adj, int src, int _snk) {
        snk = _snk;
        long long maxFlow = 0;
        long long flow = 0;
        vis.assign(adj.n, 0);
        dist.resize(adj.n);
        vid = 1;
        while (bfs(src, adj)) {
            memcpy(tmp, adj.head, adj.n * sizeof(tmp[0]));
            while (flow = dfs(src, INT_MAX, adj)) {
                maxFlow += flow;
            }
        }

        return maxFlow;
    }
} ek;

int n, m;

void test_case() {
    cin >> n;
    adj.init(n);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        --u, --v;
        adj.addAugEdge(u, v, c);
    }
    cout << ek.run(adj, 0, n - 1) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (cin >> m) {
        test_case();
    }
    return 0;
}
