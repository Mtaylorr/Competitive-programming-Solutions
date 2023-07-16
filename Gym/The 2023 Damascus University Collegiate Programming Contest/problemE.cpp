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

vector<int> adj[N];
int n, c[N];
int freq[N];
int id[N];
int sum[N];
int ans;
int sze[N];
int par[N];

void dfs(int u, int p = -1) {
    par[u] = p;
    sze[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sze[u] += sze[v];
    }
}

void solve(int u, int p, int x) {
    sum[c[u]] += x;
    for (auto v : adj[u]) {
        if (v == p) continue;
        solve(v, u, x);
    }
}
void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        freq[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        id[i] = i;
        adj[i].clear();
        cin >> c[i];
        freq[c[i]]++;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (int i = 1; i <= n; i++) {
        if (freq[i] & 1) {
            cout << -1 << endl;
            return;
        }
    }
    ans = 1e9;
    dfs(0);
    int src = -1;
    for (int i = 0; i < n; i++) {
        if (sze[i] == n / 2) {
            src = i;
        }
    }
    if (src == -1) {
        cout << -1 << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = 0;
    }
    solve(src, par[src], 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += max(0, sum[i] - freq[i] / 2);
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
