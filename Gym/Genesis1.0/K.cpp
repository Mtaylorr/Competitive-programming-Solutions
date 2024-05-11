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
} dsu;

int n, a[N];
int pos[N];
bool done[N];
void markDone(int p) {
    done[p] = 1;
    if (p - 1 >= 0 && done[p - 1]) {
        dsu.uni(p, p - 1);
    }
    if (p + 1 < n && done[p + 1]) {
        dsu.uni(p, p + 1);
    }
}
void test_case() {
    cin >> n;
    dsu.init(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        int x = pos[i];
        if (done[x]) continue;
        ans.pb(x + 1);
        int b = x - 1;
        int e = x + 1;
        if (b >= 0) {
            if (!done[b]) {
                markDone(b);
            } else {
                int l = dsu.l[dsu.getid(b)];
                l--;
                if (l >= 0 && !done[l]) {
                    markDone(l);
                }
            }
        }
        if (e < n) {
            if (!done[e]) {
                markDone(e);
            } else {
                int r = dsu.r[dsu.getid(e)];
                r++;
                if (r < n && !done[r]) {
                    markDone(r);
                }
            }
        }
        markDone(x);
    }
    cout << ans.size() << endl;
    for (auto &u : ans) {
        cout << u << " ";
    }
    cout << endl;
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
