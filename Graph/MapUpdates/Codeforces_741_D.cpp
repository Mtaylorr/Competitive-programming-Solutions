//https://codeforces.com/problemset/problem/741/D

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
int po[22];

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

int freq[1 << 22];
int val[N];
int id[N];
int n;
int dpth[N];
int ans[N];
int tin[N], tout[N], timer, sze[N], bchld[N];
int ve[N];

void dfs(int u) {
    ve[timer] = u;
    tin[u] = timer++;
    int mxsz = 0;
    int mxv = -1;
    sze[u] = 1;
    neig(u, v, e, adj) {
        val[v] = val[u] ^ po[adj.cst[e]];
        dpth[v] = dpth[u] + 1;
        dfs(v);
        sze[u] += sze[v];
        if (sze[v] > mxsz) {
            mxsz = sze[v];
            mxv = v;
        }
    }
    bchld[u] = mxv;
    tout[u] = timer - 1;
}

void calc(int u, int keep = 1) {
    neig(u, v, e, adj) {
        if (v != bchld[u]) {
            calc(v, 0);
            ans[u] = max(ans[u], ans[v]);
        }
    }
    if (bchld[u] != -1) {
        calc(bchld[u], 1);
        ans[u] = max(ans[u], ans[bchld[u]]);
    }
    if (freq[val[u]]) ans[u] = max(ans[u], freq[val[u]] - dpth[u]);
    for (int i = 0; i < 22; i++) {
        if (freq[val[u] ^ po[i]])
            ans[u] = max(ans[u], freq[val[u] ^ po[i]] - dpth[u]);
    }
    freq[val[u]] = max(freq[val[u]], dpth[u]);
    neig(u, v, e, adj) {
        if (v == bchld[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            int x = val[ve[i]];
            if (freq[x]) {
                ans[u] = max(ans[u], dpth[ve[i]] + freq[x] - 2 * dpth[u]);
            }
            for (int j = 0; j < 22; j++) {
                if (freq[x ^ po[j]])
                    ans[u] = max(ans[u],
                                 dpth[ve[i]] + freq[x ^ po[j]] - 2 * dpth[u]);
            }
        }
        for (int i = tin[v]; i <= tout[v]; i++) {
            int x = val[ve[i]];
            freq[x] = max(freq[x], dpth[ve[i]]);
        }
    }
    if (!keep) {
        for (int i = tin[u]; i <= tout[u]; i++) {
            freq[val[ve[i]]] = 0;
        }
    }
}

void solve() {
    for (int i = 0; i < 22; i++) {
        po[i] = 1 << i;
    }
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        id[i] = i;
    }
    for (int i = 1; i < n; i++) {
        int x;
        char c;
        cin >> x >> c;
        x--;
        adj.addEdge(x, i, c - 'a');
    }
    dpth[0] = 1;
    dfs(0);
    calc(0, 0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
