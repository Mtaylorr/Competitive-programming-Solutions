//https://codeforces.com/contest/723/problem/E

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

struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;

vector<int> odds[N];
int deg[N];
int n, m;
int u[N], v[N];
bool done[N];

void dfs(int x) {
    while (adj.head[x] != -1 && done[adj.cst[adj.head[x]]] == 1) {
        adj.head[x] = adj.nxt[adj.head[x]];
    }
    if (adj.head[x] == -1) {
        return;
    }
    int e = adj.head[x];
    int cst = adj.cst[e];
    int y = adj.to[e];
    u[cst] = x;
    v[cst] = y;
    done[cst] = 1;
    adj.head[x] = adj.nxt[e];
    dfs(y);
}

void test_case() {
    cin >> n >> m;
    adj.init(n);
    dsu.init(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        odds[i].clear();
        deg[i] = 0;
    }

    for (int i = 0; i <= n * n; i++) {
        done[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i];
        u[i]--, v[i]--;
        dsu.uni(u[i], v[i]);
        deg[u[i]]++;
        deg[v[i]]++;
        adj.addBiEdge(u[i], v[i], i);
    }


    for (int i = 0; i < n; i++) {
        if (deg[i] % 2) odds[dsu.getid(i)].pb(i);
        ans += (deg[i] % 2 == 0);
    }

    int cn = m;

    for (int i = 0; i < n; i++) {
        if (odds[i].size()) {
            for (int j = 0; j < odds[i].size(); j += 2) {
                int x = odds[i][j];
                int y = odds[i][j + 1];
                adj.addBiEdge(x, y, cn++);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        dfs(i);
    }
    cout << ans << "\n";
    for (int i = 0; i < m; i++) {
        cout << u[i] + 1 << " " << v[i] + 1 << "\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
