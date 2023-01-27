//https://codeforces.com/contest/1790/problem/F
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

const int E = 4e5 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

struct ADJ {
    int head[E], to[E], nxt[E], edgcnt = 0;
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
    void init(int n) {
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

const int L = 18;
int up[N][L];
int po[L];
int dpth[N];
int dpsz[N];
bool done[N];
int par[N];
int n, c[N];
int ans = 1e9;
int closest[N];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < L; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    neig(u, v, e, adj) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
    }
}
int getlca(int u, int v) {
    if (dpth[u] < dpth[v]) {
        swap(u, v);
    }
    int l = dpth[u] - dpth[v];
    for (int i = L - 1; i >= 0; i--) {
        if (po[i] <= l) {
            l -= po[i];
            u = up[u][i];
        }
    }
    for (int i = L - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    if (u != v) {
        u = up[u][0];
    }
    return u;
}

int getdist(int u, int v) {
    int lc = getlca(u, v);
    return dpth[u] + dpth[v] - 2 * dpth[lc];
}

void calcsz(int u, int p = -1) {
    dpsz[u] = 1;
    neig(u, v, e, adj) {
        if (v == p || done[v]) continue;
        calcsz(v, u);
        dpsz[u] += dpsz[v];
    }
}

int getCentroid(int u, int p, int cursz) {
    neig(u, v, e, adj) {
        if (v == p || done[v]) continue;
        if (2 * dpsz[v] >= cursz) return getCentroid(v, u, cursz);
    }
    return u;
}

int buildCentroid(int u) {
    calcsz(u, -1);
    int cursz = dpsz[u];
    int src = getCentroid(u, -1, cursz);
    done[src] = 1;
    par[src] = -1;
    neig(src, v, e, adj) {
        if (done[v]) continue;
        int x = buildCentroid(v);
        par[x] = src;
    }
    return src;
}
void upd(int u) {
    int p = u;
    while (p != -1) {
        int d = getdist(u, p);
        ans = min(ans, d + closest[p]);
        closest[p] = min(closest[p], d);
        p = par[p];
    }
}

void test_case() {
    cin >> n >> c[0];
    adj.init(n);
    c[0]--;
    for (int i = 1; i < n; i++) {
        cin >> c[i];
        c[i]--;
    }
    for (int i = 0; i < n; i++) {
        closest[i] = 1e9;
        par[i] = -1;
        done[i]=0;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    dfs(0, 0);
    int src = buildCentroid(0);
    ans = 1e9;

    upd(c[0]);
    for (int i = 1; i < n; i++) {
        upd(c[i]);
        cout << ans << " ";
    }
    cout << "\n";
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for (int i = 0; i < L; i++) {
        po[i] = 1 << i;
    }
    int T;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
