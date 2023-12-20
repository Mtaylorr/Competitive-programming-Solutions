//https://codeforces.com/contest/1913/problem/E
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

const int N = 1e5, E = 1e6;
const int MOD = 1e9 + 7;

#define neig(u, v, e) for (int e = head[u], v; (~e) && (v = to[e], 1); e = nxt[e])
int head[N], nxt[E], to[E], cap[E], cst[E], edgcnt, n, m, src, snk;
int captmp[E];
int dist[N], par[N];
int inq[N], vid = 0, fl[N];
void addEdge(int a, int b, int cs, int cp) {
    nxt[edgcnt] = head[a];
    head[a] = edgcnt;
    to[edgcnt] = b;
    cap[edgcnt] = cp;
    cst[edgcnt] = cs;
    edgcnt++;
}

void addAug(int a, int b, int cs, int c, int d = 0) {
    addEdge(a, b, cs, c);
    addEdge(b, a, -cs, d);
}

void init() {
    memset(head, -1, n * sizeof(head[0]));
    edgcnt = 0;
}

bool bellmanford() {
    queue<int> q;
    q.push(src);
    memset(dist, 63, n * sizeof(dist[0]));
    dist[src] = 0;
    inq[src] = ++vid;
    int ncnt = n;
    fl[snk] = 0, fl[src] = INT_MAX;
    while (--ncnt && q.size()) {
        int s = q.size();
        while (s--) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            neig(u, v, e) {
                if (!cap[e])
                    continue;
                int d = dist[u] + cst[e];

                if (d < dist[v]) {
                    fl[v] = min(fl[u], cap[e]);
                    dist[v] = d;
                    par[v] = e;
                    if (inq[v] != vid) {
                        inq[v] = vid;
                        q.push(v);
                    }
                }
            }
        }
    }
    return fl[snk] > 0;
}

pair<int, int> mcmf() {
    int c = 0, f = 0;
    while (bellmanford()) {
        c += dist[snk] * fl[snk];
        f += fl[snk];
        for (int u = snk; u != src; u = to[par[u] ^ 1]) {
            cap[par[u]] -= fl[snk];
            cap[par[u] ^ 1] += fl[snk];
        }
    }
    return {c, f};
}

int g[55][55];
int a[55], b[55];
void test_case() {
    int _n, _m;
    cin >> _n >> _m;
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _m; j++) {
            cin >> g[i][j];
        }
    }
    n = _n * _m + _n + _m + 2;
    src = n - 2;
    snk = n - 1;
    init();
    int tot = _n * _m;
    int sm = 0;
    for (int i = 0; i < _n; i++) {
        cin >> a[i];
        addAug(src, tot + i, 0, a[i]);
        sm += a[i];
    }

    for (int i = 0; i < _m; i++) {
        cin >> b[i];
        addAug(tot + _n + i, snk, 0, b[i]);
        sm -= b[i];
    }
    if (sm != 0) {
        cout << -1;
        return;
    }
    for (int i = 0; i < _m; i++) sm += b[i];
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _m; j++) {
            addAug(tot + i, i * _m + j, 1 - g[i][j], 1);
        }
    }
    for (int j = 0; j < _m; j++) {
        for (int i = 0; i < _n; i++) {
            addAug(i * _m + j, tot + _n + j, 0, 1);
        }
    }
    pair<int, int> rs = mcmf();
    int ans = rs.fi;
    for (int i = 0; i < _n; i++) {
        int u = tot + i;
        neig(u, v, e) {
            if (v >= 0 && v < tot && cap[e]) {
                // dbg(i, v, cap[e], cst[e]);
                ans += 1 - cst[e];
            }
        }
    }
    if (rs.se != sm) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
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
