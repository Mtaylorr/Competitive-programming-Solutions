//https://codeforces.com/problemset/problem/1156/E
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

struct DSUArray {
    vector<int> id, l, r, sz;
    DSUArray(int n) { init(n); }
    void init(int n) {
        id.assign(n, 0);
        l.assign(n, 0);
        r.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            l[i] = i;
            r[i] = i;
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
        l[v] = min(l[v], l[u]);
        r[v] = max(r[v], r[u]);
        sz[v] += sz[u];
    }
};

int p[N];
int pos[N];
int n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    DSUArray dsu = DSUArray(n);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = pos[i];
        if (x > 0 && p[x - 1] <= p[x]) {
            dsu.uni(x - 1, x);
        }
        if (x < n - 1 && p[x + 1] <= p[x]) {
            dsu.uni(x, x + 1);
        }
        
        int lf = dsu.l[dsu.getid(x)];
        int rg = dsu.r[dsu.getid(x)];
        if (x - lf < rg - x) {
            if (x - lf)
                for (int j = lf; j < x; j++) {
                    if (pos[i-p[j]]>x && dsu.sameSet(j, pos[i - p[j]])) {
                        ans++;
                    }
                }
        } else {
            if (rg - x)
                for (int j = x + 1; j <= rg; j++) {
                    if (pos[i-p[j]]<x && dsu.sameSet(j, pos[i - p[j]])) {
                        ans++;
                    }
                }
        }
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
