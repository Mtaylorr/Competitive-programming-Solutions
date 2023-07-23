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

vector<int> tree[4 * N];
int w, h, q;

void build(int id = 0, int ns = 0, int ne = h - 1) {
    for (int i = 0; i < w; i++) {
        tree[id].pb(i);
    }
    if (ns == ne) {
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
}

void mrg(vector<int> &rs, vector<int> &l, vector<int> &r) {
    for (int i = 0; i < w; i++) {
        rs[i] = (r[l[i]]);
    }
}

void upd(int p, int x, int id = 0, int ns = 0, int ne = h - 1) {
    if (ns > p || ne < p) return;
    if (ns == ne) {
        swap(tree[id][x], tree[id][x + 1]);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(p, x, l, ns, md);
    upd(p, x, r, md + 1, ne);
    mrg(tree[id], tree[l], tree[r]);
}
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

void test_case() {
    cin >> w >> h >> q;
    build();
    while (q--) {
        int a, b, y;
        cin >> y >> a >> b;
        --a, --b;
        a = min(a, b);
        y = h - y;
        upd(y, a);
        dsu.init(w);
        for (int i = 0; i < w; i++) {
            dsu.uni(i, tree[0][i]);
        }
        int ans = 0;
        for (int i = 0; i < w; i++) {
            if (dsu.getid(i) == i) {
                ans += dsu.sz[i] - 1;
            }
        }
        cout << ans << endl;
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
