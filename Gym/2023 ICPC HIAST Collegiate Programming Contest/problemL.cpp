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

int n, k, m;
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

const int MAXRT = N * 20;
template <typename T>
class DynSegTree {
   public:
    T vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    T defalt_value = 0;

    void init() { ndcnt = 0; }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    T mrg(T u, T v) { return (u + v); }

    T getval(int u) {
        if (u != -1) {
            return vals[u];
        }
        // define here the default value
        return defalt_value;
    }

    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = defalt_value;
        return ndcnt++;
    }
    void pull_up(int &id) { vals[id] = mrg(getval(lch[id]), getval(rch[id])); }

    void apply(int old_idx, int new_idx, T v) {
        vals[new_idx] = mrg(v, getval(old_idx));
    }

    template <typename... M>
    int modify(int cur, int p, int l, int r, bool inplace, const M &...v) {
        if (l == r) {
            int idx = cur;
            if (cur == -1 || !inplace) {
                idx = addnode();
            }
            apply(cur, idx, v...);
            return idx;
        }
        int md = l + (r - l) / 2;
        int idx = cur;
        if (cur == -1 || !inplace) {
            idx = addnode();
        }
        if (p <= md) {
            lch[idx] = modify(left(cur), p, l, md, inplace, v...);
            rch[idx] = right(cur);
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), p, md + 1, r, inplace, v...);
        }
        pull_up(idx);
        return idx;
    }

    int firstOnCondition(int nd, int qs, int qe, int l, int r,
                         function<bool(int)> ch) {
        if (qs > r || qe < l) return -1;
        if (qs <= l && qe >= r) {
            if (ch(getval(nd))) {
                return -1;
            }
        }
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int x = firstOnCondition(left(nd), qs, qe, l, md, ch);
        if (x == -1) {
            return firstOnCondition(right(nd), qs, qe, md + 1, r, ch);
        }
        return x;
    }

    T query(int nd, int qs, int qe, int l, int r) {
        if (qs > qe) return 0;
        if (qs <= l && qe >= r) {
            return getval(nd);
        }
        int md = l + (r - l) / 2;
        if (qe <= md) {
            return query(left(nd), qs, qe, l, md);
        } else {
            if (qs > md) {
                return query(right(nd), qs, qe, md + 1, r);
            } else {
                return mrg(query(left(nd), qs, qe, l, md),
                           query(right(nd), qs, qe, md + 1, r));
            }
        }
    }
};
DynSegTree<int> sg;

ll cst[N];
ll val[N];
int tin[N], tout[N], ti = -1;
vector<int> adds[N];
int nbleafs[N];
void dfs(int u, int p = -1) {
    tin[u] = ++ti;
    nbleafs[u] = 0;
    neig(u, v, e, adj) {
        if (v == p) continue;
        dfs(v, u);
        nbleafs[u] += nbleafs[v];
        cst[v] = adj.cst[e];
    }
    nbleafs[u] = max(nbleafs[u], 1);
    tout[u] = ti;
}
ll dp[10004][1003];
ll tmp[1003];
int roots[N];
int sz[N];
void solve(int u, int p = -1) {
    for (int i = 0; i <= k; i++) {
        dp[u][i] = 0;
    }
    sz[u] = 0;
    neig(u, v, e, adj) {
        if (v == p) continue;
        solve(v, u);
        sz[u] += nbleafs[v];
        for (int i = 0; i <= k; i++) {
            tmp[i] = 0;
        }
        for (int j = 0; j <= min(sz[u], k); j++) {
            for (int o = 0; o <= min(j, min(k, nbleafs[v])); o++) {
                tmp[j] = max(tmp[j], dp[v][o] + dp[u][j - o]);
            }
        }
        for (int i = 0; i <= k; i++) {
            dp[u][i] = tmp[i];
        }
    }
    for (int i = 1; i <= k; i++) {
        dp[u][i] = max(dp[u][i], dp[u][i - 1]);
    }
    for (int i = k - 1; i >= 1; i--) {
        dp[u][i] += cst[u];
    }
}

void test_case() {
    cin >> n >> k >> m;
    ti = -1;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        adds[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj.addBiEdge(--u, --v, w);
    }
    dfs(0);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x == y) continue;
        --x, --y;
        x = tin[x];
        y = tin[y];
        adds[x].pb(y);
        adds[y].pb(x);
    }
    sg.init();
    sg.addnode();
    roots[0] = 0;
    for (int i = 1; i <= n; i++) {
        roots[i] = roots[i - 1];
        for (auto v : adds[i - 1]) {
            roots[i] = sg.modify(roots[i], v, 0, n, 0, 1);
        }
    }
    vector<ll> ord;
    ll sum = 0;
    for (int i = 1; i < n; i++) {
        ll cost = sg.query(roots[tout[i] + 1], tout[i] + 1, n, 0, n);
        cost -= sg.query(roots[tin[i]], tout[i] + 1, n, 0, n);
        cost += sg.query(roots[tout[i] + 1], 0, tin[i] - 1, 0, n);
        cost -= sg.query(roots[tin[i]], 0, tin[i] - 1, 0, n);
        cst[i] *= cost;
        sum += cst[i];
    }
    solve(0);
    ll ans = 0;
    for (int i = 0; i <= k; i++) {
        ans = max(ans, dp[0][i]);
    }
    cout << sum - ans << endl;
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
