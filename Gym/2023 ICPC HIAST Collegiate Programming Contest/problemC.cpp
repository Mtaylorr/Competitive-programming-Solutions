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

int n;
ll dp[N];
vector<int> adj[N];
long double ans = 0;

void solve(int u, int p = -1) {
    dp[u] = 1;
    ll sm = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        solve(v, u);
        ans += (n - dp[v]) * dp[v];
        dp[u] += dp[v];
    }
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    ans = 0;
    solve(0);
    ans *= (2.0 / ((n) * (1.0)));
    cout << fixed << setprecision(10) << ans << "\n";
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
