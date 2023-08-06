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
const int N = 1e6 + 5;

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
vector<int> pos[N];
int n, a[N], m;

void test_case() {
    cin >> n >> m;
    dsu.init(n);
    for (int i = 0; i <= m; i++) {
        pos[i].clear();
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].pb(i);
    }
    ll ans = 0;
    for (int i = m; i >= 1; i--) {
        int bef = -1;
        for (int j = i; j <= m; j += i) {
            for (auto &v : pos[j]) {
                if (bef == -1) {
                    bef = v;
                    continue;
                }
                if (!dsu.sameSet(v, bef)) {
                    ans += i;
                    dsu.uni(v, bef);
                }
                bef = v;
            }
        }
    }
    cout << ans << endl;
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
