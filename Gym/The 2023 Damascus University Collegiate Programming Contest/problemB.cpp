// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
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

int sz[N];
vector<int> id[N];
vector<int> upds[N];
vector<int> ans[N];
set<int> vals[N];
int ty[N];
int u, v, t, x;
int res[N];
int a[N];
int n, q;

int getrepr(int u, int t) {
    assert(t >= 1);
    int p = upper_bound(all(upds[u]), t) - upds[u].begin();
    return p - 1;
}

int getid(int u, int t) {
    int idrepr = getrepr(u, t);
    assert(idrepr>=0 && idrepr<id[u].size());
    if (id[u][idrepr] == u) {
        return u;
    }
    return getid(id[u][idrepr], t);
}

void init() {
    for (int i = 0; i < n; i++) {
        sz[i] = 1;
        id[i].pb(i);
        upds[i].pb(0);
        ans[i].pb(1);
        vals[i].insert(a[i]);
    }
}

void mrg(int u, int v, int t) {
    u = getid(u, t);
    v = getid(v, t);
    if (u == v) return;
    int repu = getrepr(u, t);
    int repv = getrepr(v, t);

    if (sz[u] < sz[v]) {
        swap(u, v);
        swap(repu, repv);
    }
    upds[u].pb(t);
    upds[v].pb(t);
    id[u].pb(u);
    id[v].pb(u);
    sz[u] += sz[v];
    int rs = ans[u][repu];
    for (auto &x : vals[v]) {
        int cnt0 = vals[u].count(x);
        if (cnt0) continue;
        int cnt1 = vals[u].count(x - 1);
        int cnt2 = vals[u].count(x + 1);
        if (cnt1 && cnt2) {
            rs--;
        } else if (cnt1 == 0 && cnt2 == 0) {
            rs++;
        }
        vals[u].insert(x);
    }
    vals[v].clear();
    ans[u].pb(rs);
    ans[v].pb(ans[v][repv]);
}

int srch(int u, int t) {
    u = getid(u, t);
    int idrepr = getrepr(u, t);
    return ans[u][idrepr];
}

void test_case() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    init();
    for (int i = 1; i <= q; i++) {
        cin >> ty[i];
        if (ty[i] == 1) {
            cin >> u >> v >> x;
            if (x > 0 && ty[x] == 2) {
                x = res[x];
            } else {
                x = 1;
            }
            u = (u * 1ll * x) % n;
            v = (v * 1ll * x) % n;
            if (u == v) continue;
            mrg(u, v, i);
        } else {
            cin >> u >> t >> x;
            if (x > 0 && ty[x] == 2) {
                x = res[x];
            } else {
                x = 1;
            }
            u = (u * 1ll * x) % n;
            t = (t * 1ll * x) % i + 1;
            res[i] = srch(u, t);
            cout << res[i] << endl;
        }
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
