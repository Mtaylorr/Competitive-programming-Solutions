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

int n, m, s, k;
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
bool vis[N][7];
int dist[N][7];

void dijk() {
    set<pair<int, pair<int, int> > > pq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            dist[i][j] = 1e9;
            vis[i][j] = 0;
        }
    }
    dist[s][0] = 0;
    pq.insert({0, {s, 0}});
    pair<int, pair<int, int> > p;
    while (!pq.empty()) {
        p = *pq.begin();
        pq.erase(pq.begin());
        int u = p.se.fi;
        int day = p.se.se;
        int di = p.fi;
        if (vis[u][day]) continue;
        vis[u][day] = 1;
        neig(u, v, e, adj) {
            int nday = (adj.cst[e] + 1) % 7;
            int diff = 0;
            if (adj.cst[e] >= day) {
                diff = adj.cst[e] - day + 1;
            } else {
                diff = 7 - (day - adj.cst[e] - 1);
            }
            if (vis[v][nday] || dist[v][nday] <= di + diff) {
                continue;
            }
            dist[v][nday] = di + diff;
            pq.insert({di + diff, {v, nday}});
        }
    }
}

void test_case() {
    cin >> n >> m;
    cin >> s >> k;
    s--, k--;
    adj.init(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        c--;
        adj.addBiEdge(a, b, c);
    }
    dijk();
    int ans = 1e9;
    for (int i = 0; i < 7; i++) {
        ans = min(ans, dist[k][i]);
    }
    cout << ans << endl;
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
