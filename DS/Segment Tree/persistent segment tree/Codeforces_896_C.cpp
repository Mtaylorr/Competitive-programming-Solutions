//https://codeforces.com/contest/896/problem/C
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

#define MODDtype ll

MODDtype powe(MODDtype u, ll v, MODDtype mod = MOD) {
    MODDtype ans = 1;
    MODDtype acc = u % mod;
    while (v) {
        if (v % 2) ans = (ans * 1ll * acc) % mod;
        acc = (acc * 1ll * acc) % mod;
        v /= 2;
    }
    return ans;
}

int seed;
int n, m, vmax;
ll a[N];
int l[N], r[N], x[N], y[N], op[N];
int rnd() {
    int rs = seed;
    seed = (seed * 7ll + 13) % MOD;
    return rs;
}

void getinput() {
    for (int i = 1; i <= n; i++) {
        a[i] = (rnd() % vmax) + 1;
    }
    for (int i = 0; i < m; i++) {
        op[i] = (rnd() % 4) + 1;
        l[i] = (rnd() % n) + 1;
        r[i] = (rnd() % n) + 1;

        if (l[i] > r[i]) {
            swap(l[i], r[i]);
        }
        if (op[i] == 3) {
            x[i] = (rnd() % (r[i] - l[i] + 1)) + 1;
        } else {
            x[i] = (rnd() % vmax) + 1;
        }
        if (op[i] == 4) {
            y[i] = (rnd() % vmax) + 1;
        }

    }
}

typedef ll dtype;
vector<dtype> tree[4 * N][2];
dtype lazy[4 * N];
int lazyType[4 * N];
dtype NULL_Lazy = 0;

bool has_lazy(int id) { return lazy[id] != NULL_Lazy; }

void rem_lazy(int id) {
    lazy[id] = NULL_Lazy;
    lazyType[id] = 0;
}

void unlazy(int id, int ns, int ne) {
    //dbg(id, ns, ne, lazyType[id], lazy[id]);
    if (lazyType[id] == 1) {
        for (auto &u : tree[id][0]) {
            u += lazy[id];
        }
    } else if (lazyType[id] == 2) {
        tree[id][0] = {lazy[id]};
        tree[id][1] = {ne - ns + 1};
    }
}

void propagate(int id, int chld) {
    if (lazyType[chld] == 0) {
        lazy[chld] = lazy[id];
        lazyType[chld] = lazyType[id];
    } else if (lazyType[id] == 2) {
        lazy[chld] = lazy[id];
        lazyType[chld] = lazyType[id];
    } else if (lazyType[id] == 1) {
        lazy[chld] += lazy[id];
    }
}

void upd_lazy(int id, int ns, int ne) {
    if (has_lazy(id)) {
        unlazy(id, ns, ne);
        if (ns != ne) {
            int l = 2 * id + 1;
            int r = 2 * id + 2;
            propagate(id, l);
            propagate(id, r);
        }
        rem_lazy(id);
    }
}

void mrg(int id, int l, int r) {
    tree[id][0].clear();
    tree[id][1].clear();
    int i = 0;
    int j = 0;
    while (i < tree[l][0].size() && j < tree[r][0].size()) {
        if (tree[l][0][i] < tree[r][0][j]) {
            tree[id][0].pb(tree[l][0][i]);
            tree[id][1].pb(tree[l][1][i]);
            i++;
        } else if (tree[l][0][i] > tree[r][0][j]) {
            tree[id][0].pb(tree[r][0][j]);
            tree[id][1].pb(tree[r][1][j]);
            j++;
        } else {
            tree[id][0].pb(tree[r][0][j]);
            tree[id][1].pb(tree[l][1][i] + tree[r][1][j]);
            i++;
            j++;
        }
    }
    while (i < tree[l][0].size()) {
        tree[id][0].pb(tree[l][0][i]);
        tree[id][1].pb(tree[l][1][i]);
        i++;
    }
    while (j < tree[r][0].size()) {
        tree[id][0].pb(tree[r][0][j]);
        tree[id][1].pb(tree[r][1][j]);
        j++;
    }
}

void build(int id = 0, int ns = 1, int ne = n) {
    lazy[id] = NULL_Lazy;
    if (ns == ne) {
        tree[id][0] = {a[ns]};
        tree[id][1] = {1};
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    mrg(id, l, r);
}

void upd(int qs, int qe, dtype v, int ty, int id = 0, int ns = 1, int ne = n) {
    upd_lazy(id, ns, ne);
    
    if (qs > ne || qe < ns) {
        return;
    }
    if (qs <= ns && qe >= ne) {
        
        lazy[id] = v;
        lazyType[id] = ty;
        upd_lazy(id, ns, ne);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(qs, qe, v,ty,  l, ns, md);
    upd(qs, qe, v,ty,  r, md + 1, ne);
    mrg(id, l, r);
}

dtype query(int qs, int qe, ll x, int y, int id = 0, int ns = 1, int ne = n) {
    upd_lazy(id, ns, ne);
    if (qs > ne || qe < ns) {
        return 0;
    }
    if (qs <= ns && qe >= ne) {
        if (y == -1) {
            int rs = 0;
            for (int i = 0; i < tree[id][0].size();i++) {
                if (tree[id][0][i] < x) rs += tree[id][1][i];
            }
            return rs;
        }
        ll rs = 0;
        for (int i = 0; i < tree[id][0].size(); i++) {
            rs =
                (rs + ((tree[id][1][i] % y) * powe(tree[id][0][i], x, y)) % y) %
                y;
        }
        return rs;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    if(y==-1)
    return query(qs, qe, x, y, l, ns, md) + query(qs, qe, x, y, r, md + 1, ne);
    
    return (query(qs, qe, x, y, l, ns, md) + query(qs, qe, x, y, r, md + 1, ne))%y;
}

void solve() {
    cin >> n >> m >> seed >> vmax;
    getinput();
    build();
    for (int i = 0; i < m; i++) {
        //dbg(op[i],l[i],r[i],x[i]);
        if (op[i] == 1) {
            upd(l[i], r[i], x[i], 1);
        } else if (op[i] == 2) {
            upd(l[i], r[i], x[i], 2);
        } else if (op[i] == 3) {
            ll lf = 0;
            ll rg = 1e17;
            while (lf < rg) {
                ll md = (lf + rg + 1) / 2;
                int bef = query(l[i], r[i], md, -1);
                if (bef <= x[i] - 1) {
                    lf = md;
                } else {
                    rg = md - 1;
                }
            }
            cout << lf << endl;
        } else {
            cout << query(l[i], r[i], x[i], y[i]) << endl;
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
