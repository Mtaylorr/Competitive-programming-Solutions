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
const int N = 205 + 5;
const int MOD = 1e9 + 7;

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

string s;
int n, k;
set<int> st[N];
void test_case() {
    cin >> n >> k;
    cin >> s;
    vector<int> divs;
    divs.pb(0);
    for (int i = 1; i <= k; i++) {
        if ((n) % i == 0) {
            divs.pb(i);
        }
    }
    int m = divs.size();
    int ans = 0;
    for (int mask = 0; mask < (1 << m); ++mask) {
        dsu.init(n);
        int nb = 0;
        for (int i = 0; i < m; i++) {
            if ((1 << i) & mask) {
                nb++;
                for (int j = 0; j < n; j++) {
                    int l = (j + divs[i]) % n;
                    int r = ((n - 1 - j) + divs[i]) % n;
                    dsu.uni(l, r);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            st[i].clear();
        }
        for (int i = 0; i < n; i++) {
            if (s[i] == '?') continue;
            st[dsu.getid(i)].insert(s[i] - 'a');
        }
        int x = 1;
        for (int i = 0; i < n; i++) {
            if (i == dsu.getid(i)) {
                if (st[i].size() == 0) {
                    x = (x * 1ll * 26) % MOD;
                } else if (st[i].size() >= 2) {
                    x = 0;
                }
            }
        }
        if (nb % 2 == 0 && nb > 0) {
            ans = (ans + MOD + 0ll - x) % MOD;
        } else if (nb % 2) {
            ans = (ans + x) % MOD;
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
    while (T--) {
        test_case();
    }
    return 0;
}
