//https://codeforces.com/group/YTYmnVxV00/contest/101485/attachments/download/5845/20152016-northwestern-european-regional-contest-nwerc-2015-en.pdf problem G
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

struct FenwickTree {
    vector<int> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    int mrg(int &x, int &y) { return x + y; }

    void upd(int x, int v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    int getprefix(int x) {
        if (x == 0) return 0;
        int rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    int getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
} ft[4 * N];

int n;
vector<int> tree[4 * N];

int a[3][N];
bool vis[4][N];
int x[3][N];
int ind[3];
int st, en;
int qi[N], qans[N];


void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        int z = a[1][ns];
        tree[id] = {x[2][z-1]};
        ft[id].init(sz(tree[id]) + 1);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    merge(tree[l].begin(), tree[l].end(), tree[r].begin(), tree[r].end(),
          inserter(tree[id], tree[id].begin()));
    ft[id].init(sz(tree[id]) + 1);
}

int query(int qs, int qe, int qv, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns > qe || ne < qs) return 0;
    if (qs <= ns && qe >= ne) {
        int p = lower_bound(tree[id].begin(), tree[id].end(), qv) -
                tree[id].begin();
        return ft[id].getprefix(p);
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return query(qs, qe, qv, l, ns, md) + query(qs, qe, qv, r, md + 1, ne);
}

void upd(int qp, int qv, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns > qp || ne < qp) return;
    if (ns <= qp && ne >= qp) {
        int p = lower_bound(tree[id].begin(), tree[id].end(), qv) -
                tree[id].begin();
        p++;
        ft[id].upd(p, 1);
    }
    if (ns == ne) return;
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(qp, qv, l, ns, md);
    upd(qp, qv, r, md + 1, ne);
}

void solve() {
    cin >> n;
    ll ans = 0;
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < n; i++) {
            cin >> a[j][i];
            x[j][a[j][i] - 1] = i;
        }
    build();
    for (int i = 0; i < n; i++) {
        int y = x[1][a[0][i] - 1];
        int z = x[2][a[0][i] - 1];
        ans+=query(0,y,z);
        upd(y,z);
    }
    cout << ans;
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
