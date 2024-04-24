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

#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

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

const int L = 18;
class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po[L];

    void run(int src, ADJ &adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        dpth[src] = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ &adj) {
        up[u][0] = p;
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            dpth[v] = dpth[u] + 1;
            dfs(v, u, adj);
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

    int getkthpar(int u, int k) {
        for (int i = L - 1; i >= 0; i--) {
            if (k >= po[i]) {
                u = up[u][i];
                k -= po[i];
            }
        }
        return u;
    }
    int getkthonpath(int u, int v, int k) {
        int lc = getlca(u, v);
        int d = dpth[u] - dpth[lc];
        if (d >= k) return getkthpar(u, k);
        d = dpth[u] + dpth[v] - 2 * dpth[lc];
        return getkthpar(v, d - k);
    }

    int getdist(int u, int v) {
        int lc = getlca(u, v);
        return dpth[u] + dpth[v] - 2 * dpth[lc];
    }
} LCA;

const int MOD = 1e9 + 7;
const int B = 1e5 + 3;

int n, a[N];
int roots[N];
int po[N];
const int MAXRT = N * 30;
template <typename T>
class DynSegTree {
   public:
    T vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    T defalt_value = 0;

    void init() { ndcnt = 0; }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    T mrg(T u, T v) { return (u + v) % MOD; }

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

    void apply(int old_idx, int new_idx, T v) { vals[new_idx] = mrg(v, getval(old_idx)); }

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

    int firstOnCondition(int e, int b, int ab, int vab, int c, int d, int cd, int vcd, int qs, int qe, int l, int r) {
        if (qs > r || qe < l) return -1;
        int hab = (getval(e) + 0ll + getval(b) + MOD - (2ll * getval(ab)) % MOD) % MOD;
        if (vab <= r && vab >= l) hab = (hab + po[vab]) % MOD;
        int hcd = (getval(c) + 0ll + getval(d) + MOD - (2ll * getval(cd)) % MOD) % MOD;
        if (vcd <= r && vcd >= l) hcd = (hcd + po[vcd]) % MOD;
        if (qs <= l && qe >= r) {
            if (hab == hcd) return -1;
        }
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int x = firstOnCondition(left(e), left(b), left(ab), vab, left(c), left(d), left(cd), vcd, qs, qe, l, md);
        if (x == -1) {
            return firstOnCondition(right(e), right(b), right(ab), vab, right(c), right(d), right(cd), vcd, qs, qe, md + 1, r);
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
                return mrg(query(left(nd), qs, qe, l, md), query(right(nd), qs, qe, md + 1, r));
            }
        }
    }
};
DynSegTree<int> sg;

void dfs(int u, int p = -1) {
    neig(u, v, e, adj) {
        if (v == p) continue;
        roots[v] = sg.modify(roots[u], a[v], 1, 1e5, 0, po[a[v]]);
        dfs(v, u);
    }
}

void test_case() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    po[0] = 1;
    for (int i = 1; i <= 1e5; i++) {
        po[i] = (B * 1ll * po[i - 1]) % MOD;
    }
    LCA.run(0, adj);
    sg.init();
    sg.addnode();
    roots[0] = sg.modify(roots[0], a[0], 1, 1e5, 1, po[a[0]]);
    //
    dfs(0);

    int q;
    cin >> q;
    while (q--) {
        int u1, v1, u2, v2, k;
        cin >> u1 >> v1 >> u2 >> v2 >> k;
        --u1, --v1, --u2, --v2;
        int lc1 = LCA.getlca(u1, v1);
        int lc2 = LCA.getlca(u2, v2);
        int cura = 0;
        vector<int> ans;
        while (k-- && cura < 1e5) {
            int r = sg.firstOnCondition(roots[u1], roots[v1], roots[lc1],a[lc1], roots[u2], roots[v2], roots[lc2],a[lc2], cura + 1, 1e5, 1, 1e5);
            if (r == -1) break;
            ans.pb(r);
            cura = r;
        }
        cout << ans.size() << " ";
        for (auto &u : ans) {
            cout << u << " ";
        }
        cout << "\n";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
