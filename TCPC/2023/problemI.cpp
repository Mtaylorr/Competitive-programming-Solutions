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
const int MOD = 1e9 + 7;

const int MAXRT = N * 40;
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

vector<int> adj[N];
int n;
int b[N], dp[N], sum[N], a[N], bchd[N], sz[N], tin[N], tout[N], ti = -1;
bool isleaf[N];
vector<int> nodes;

void dfs(int u, int p = -1) {
    int nb = 0;
    int mxv = -1;
    int mxsz = 0;
    tin[u] = ++ti;
    nodes.pb(u);
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        nb++;
        if (sz[v] > mxsz) {
            mxsz = sz[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = ti;
    isleaf[u] = nb == 0;
}
int src;

void solve(int u, int p = -1, bool keep = 0) {
    if (u == -1) return;
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        solve(v, u, 0);
        sum[u] = (sum[u] + 0ll + sum[v] + 0ll + dp[v]) % MOD;
    }
    if (bchd[u] != -1) {
        solve(bchd[u], u, 1);
        sum[u] = (sum[u] + 0ll + sum[bchd[u]] + 0ll + dp[bchd[u]]) % MOD;
    }
    if (isleaf[u]) {
        a[u] = b[u];
    } else {
        a[u] = (b[u] * 1ll * sum[u]) % MOD;
    }
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[u]; i++) {
            int node = nodes[i];
            src = sg.modify(src, a[node], 0, 1e9 + 7, 1, dp[node]);
        }
    }
    dp[u] = 1 + sg.query(src, a[u] + 1, 1e9 + 7, 0, 1e9 + 7);
    if (!keep) {
        sg.init();
        src = sg.addnode();
    }
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[--u].pb(--v);
        adj[v].pb(u);
    }
    dfs(0);
    sg.init();
    src = sg.addnode();
    solve(0);
    for (int i = 0; i < n; i++) {
        cout << dp[i] << " ";
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
