//https://www.codechef.com/problems/MCO16504
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

int n, m, D, S;
vector<ll> c;
int u[N], v[N], qpos[N];
int ty[N], x[N], y[N];
int s[N], t[N], k[N];
bool exec[N];
int ans[N];

struct dsu_save {
    int v, rnkv, u, rnku;

    dsu_save() {}

    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

struct dsu_with_rollbacks {
    vector<int> p, rnk;
    int comps;
    stack<dsu_save> op;
    vector<ll> sz;

    dsu_with_rollbacks() {}

    dsu_with_rollbacks(int n, vector<ll> &c) {
        p.resize(n);
        rnk.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rnk[i] = 0;
            sz[i] = c[i];
        }
        comps = n;
    }

    int find_set(int v) { return (v == p[v]) ? v : find_set(p[v]); }

    bool unite(int v, int u) {
        v = find_set(v);
        u = find_set(u);
        if (v == u) return false;
        comps--;
        if (rnk[v] > rnk[u]) swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        sz[u] += sz[v];
        if (rnk[u] == rnk[v]) rnk[u]++;
        return true;
    }

    void rollback() {
        if (op.empty()) return;
        dsu_save x = op.top();
        op.pop();
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
        sz[x.u] -= sz[x.v];
    }
} dsu;

pair<int, int> getpair(int x, int y) { return {min(x, y), max(x, y)}; }

map<pair<int, int>, int> pos;

void add_query(int id,int c){
    if(ty[id]==1){
        if(c==1){
            exec[id]=dsu.unite(x[id], y[id]);
        }else{
            if(exec[id])dsu.rollback();
        }
    }else if(ty[id]==2){
        int p =dsu.find_set(x[id]);
        dsu.sz[dsu.find_set(x[id])]+=y[id]*c;
    }
}

void rec(int low, int high, vector<int> &queries, int &d_idx) {
    if (queries.size() == 0) return;
    int md = low + (high - low) / 2;
    while (d_idx > md) {
        add_query(--d_idx, +1);
    }
    while (d_idx < md) {
        add_query(d_idx++, -1);
    }
    vector<int> left_queries, right_queries;
    for (auto qu : queries) {
        int ps = dsu.find_set(s[qu]);
        int pt = dsu.find_set(t[qu]);
        ll sm = dsu.sz[ps] + dsu.sz[pt];
        if (sm >= k[qu]) {
            ans[qu] = md;
            right_queries.pb(qu);
        } else {
            left_queries.pb(qu);
        }
    }
    queries.clear();
    if (low == high) return;
    rec(low, md, left_queries, d_idx);
    rec(md + 1, high, right_queries, d_idx);
}

void solve() {
    cin >> n >> m >> D >> S;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        c.pb(x);
    }

    vector<int> ord;
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i];
        --u[i], --v[i];
        pos[getpair(u[i], v[i])] = i;
        qpos[i] = 1e9;
        ord.pb(i);
    }
    for (int i = 0; i < D; i++) {
        cin >> ty[i] >> x[i] >> y[i];
        if (ty[i] == 1) {
            --x[i], --y[i];
            pair<int, int> p = getpair(x[i], y[i]);
            qpos[pos[p]] = i;
        } else {
            --x[i];
            c[x[i]] -= y[i];
        }
    }
    sort(all(ord), [](int &a, int &b) { return qpos[a] >qpos[b]; });
    dsu = dsu_with_rollbacks(n, c);
    for (int i = 0; i < m; i++) {
        if (qpos[i] == 1e9) {
            dsu.unite(u[i], v[i]);
        }
    }
    vector<int> queries;
    for (int i = 0; i < S; i++) {
        queries.pb(i);
        cin >> s[i] >> t[i] >> k[i];
        ans[i] = 1e9;
        --s[i], --t[i];
    }
    int d_idx = D;
    rec(0, D , queries, d_idx);
    for (int i = 0; i < S; i++) {
        if (ans[i] < 1e9) {
            cout << ans[i] << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
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
        solve();
    }
    return 0;
}
