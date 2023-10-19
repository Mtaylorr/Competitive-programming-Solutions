//https://codeforces.com/problemset/problem/527/E
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
const int N = 5e5 + 5;

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

const int MAXM_EULER = N;

class EulerPath {
   public:
    int u[MAXM_EULER], v[MAXM_EULER];
    bool done[MAXM_EULER];
    ADJ adj;

    void init(int n, int m) {
        memset(done, 0, m * sizeof(done[0]));
        adj.init(n);
    }
    void run() {
        for (int i = 0; i < adj.n; i++) {
            dfs(i);
        }
    }

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
} euler;

int n, m;
int a[N], b[N];
int cnt[N];
int nb[N];
int indeg[N], outdeg[N];

int isodd[N];
bool vis[N];

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    neig(u, v, e, adj) {
        if (vis[v]) continue;
        dfs(v);
        if (isodd[v]) {
            int w = adj.cst[e];
            swap(euler.u[w], euler.v[w]);
            isodd[u] ^= 1;
            isodd[v] ^= 1;
        }
    }
}

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        --a[i], --b[i];
        if (a[i] == b[i]) {
            nb[a[i]] ^= 1;
        } else {
            cnt[a[i]]++;
            cnt[b[i]]++;
        }
    }
    vector<int> tmp;
    for (int i = 0; i < n; i++) {
        if (cnt[i] % 2) {
            tmp.pb(i);
        }
    }
    for (int i = 0; i < tmp.size(); i += 2) {
        a[m] = tmp[i];
        b[m++] = tmp[i + 1];
    }
    euler.init(n, m);
    adj.init(n);
    for (int i = 0; i < m; i++) {
        if (a[i] != b[i]) {
            euler.adj.addBiEdge(a[i], b[i], i);
            adj.addBiEdge(a[i], b[i], i);
        }
    }
    euler.run();
    for (int i = 0; i < m; i++) {
        if (a[i] != b[i]) {
            indeg[euler.v[i]]++;
            outdeg[euler.u[i]]++;
        }
    }
    for (int i = 0; i < n; i++) {
        if ((indeg[i] + nb[i]) % 2) {
            isodd[i] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i);
    }
    tmp.clear();
    vector<pair<int, int> > extra;
    for (int i = 0; i < n; i++) {
        if (isodd[i]) {
            extra.pb({i, i});
        }
    }
    cout << m + extra.size() << endl;
    for (int i = 0; i < m; i++) {
        if (a[i] != b[i]) {
            cout << euler.u[i] + 1 << " " << euler.v[i] + 1 << "\n";
        } else {
            cout << a[i] + 1 << " " << a[i] + 1 << "\n";
        }
    }
    for (auto &x : extra) {
        cout << x.fi + 1 << " " << x.se + 1 << "\n";
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
