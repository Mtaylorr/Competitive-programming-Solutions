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

int n, m, k;
ll dist[10005][105];
bool vis[10005][105];
int cst[N];
void dijk(int src) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dist[i][j] = 1e18;
            vis[i][j] = 0;
        }
    }
    set < pair<ll, pair<int, int> > > pq;
    pq.insert({0, {src, 0}});
    dist[src][0] = 0;
    pair<ll, pair<int, int> > p;
    while (!pq.empty()) {
        p = (*pq.begin());
        pq.erase(pq.begin());
        ll d = p.fi;
        int u = p.se.fi;
        int r = p.se.se;
        if (vis[u][r]) continue;
        vis[u][r]=1;
        neig(u, v, e, adj) {
            if (vis[v][r] == 0 && dist[v][r] > d + adj.cst[e]) {
                dist[v][r] = d + adj.cst[e];
                pq.insert({dist[v][r], {v, r}});
            }
            if (r + 1 <= k && dist[v][r + 1] > d + cst[e / 2]) {
                dist[v][r + 1] = d + cst[e / 2];
                pq.insert({dist[v][r + 1], {v, r+1}});
            }
        }
    }
}

void test_case() {
    cin >> n >> m >> k;
    adj.init(n);
    int s, e;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj.addBiEdge(u, v, w);
        int x = w;
        cst[i] = w;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                cst[i] = min(cst[i], w / j + 2 * j);
                while (x % j == 0) {
                    x /= j;
                }
            }
        }
        if (x > 1) {
            cst[i] = min(cst[i], w / x + 2 * x);
        }
    }
    cin >> s >> e;
    --s, --e;
    dijk(s);
    ll ans = 1e18;
    for (int j = 0; j <= k; j++) {
        ans = min(ans, dist[e][j]);
    }
    if (ans < 1e18) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
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
