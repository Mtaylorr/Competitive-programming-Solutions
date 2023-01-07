//https://codeforces.com/contest/932/problem/F

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
const int N = 2e5 + 5;

const int MAXND_LI_CHAO = N * 40;

typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) { return (conj(a) * b).x(); }

ftype f(point a, ftype x) { return dot(a, {x, 1}); }

struct LiChaoTree {
    point vals[MAXND_LI_CHAO];
    point initial_pt = {0, (long long)1e18};
    int lch[MAXND_LI_CHAO], rch[MAXND_LI_CHAO], ndcnt = 0;
    ftype lb, ub;
    int init(ftype _lb, ftype _ub) {
        lb = _lb;
        ub = _ub;
        ndcnt = 0;
        return addnode();
    }
    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }
    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = initial_pt;
        return ndcnt++;
    }
    int addnode(int p) {
        int np = addnode();
        if (p != -1) vals[np] = vals[p];
        return np;
    }

    int modify(int cur, int l, int r, point nw) {
        if (cur == -1) {
            int idx = addnode();
            vals[idx] = nw;
            return idx;
        }
        int idx = addnode(cur);
        int md = (l + r) / 2;
        bool lef = f(nw, l) < f(vals[idx], l);
        bool mid = f(nw, md) < f(vals[idx], md);
        if (mid) {
            swap(vals[idx], nw);
        }
        if (r - l == 1) {
            return idx;
        } else if (lef != mid) {
            lch[idx] = modify(left(cur), l, md, nw);
            rch[idx] = right(cur);
            return idx;
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), md, r, nw);
            return idx;
        }
    }
    ftype query(int nd, ftype x, int l, int r) {
        if (nd == -1) {
            return f(initial_pt, x);
        }
        int md = (l + r) / 2;
        if (r - l + 1 == 1) {
            return f(vals[nd], x);
        } else if (x < md) {
            return min(f(vals[nd], x), query(left(nd), x, l, md));
        } else {
            return min(f(vals[nd], x), query(right(nd), x, md, r));
        }
    }

    int modify(int cur, point nw) { return modify(cur, lb, ub, nw); }

    ftype query(int nd, ftype x) { return query(nd, x, lb, ub); }
} lichao;

int n;
ll a[N], b[N];
vector<int> adj[N];
ll dp[N];
int subsz[N], bchd[N];
bool isleaf[N];
int tin[N], tout[N], ve[N], timer = -1;

void dfs(int u, int p = -1) {
    tin[u] = ++timer;
    ve[timer] = u;
    subsz[u] = 1;
    int mxsz = -1;
    int mxv = -1;
    isleaf[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        isleaf[u] = 0;
        dfs(v, u);
        subsz[u] += subsz[v];
        if (subsz[v] > mxsz) {
            mxsz = subsz[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = timer;
}

int dfs1(int u, bool keep, int p = -1) {
    int src = -1;
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        dfs1(v, 0, u);
    }
    if (bchd[u] != -1) {
        src = dfs1(bchd[u], 1, u);
    }
    if (src == -1) {
        src = lichao.addnode();
    }

    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        for (int l = tin[v]; l <= tout[v]; l++) {
            src = lichao.modify(src, {b[ve[l]], dp[ve[l]]});
        }
    }

    dp[u] = lichao.query(src, a[u]);

    if (isleaf[u]) {
        dp[u] = 0;
    }
    src = lichao.modify(src, {b[u], dp[u]});
    if (!keep) {
        src = lichao.init(-2e5, 2e5);
    }
    return src;
}

void test_case() {
    cin >> n;
    lichao.init(-2e5, 2e5);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        adj[x].pb(y);
        adj[y].pb(x);
    }

    dfs(0, -1);
    dfs1(0, 0, -1);

    for (int i = 0; i < n; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
