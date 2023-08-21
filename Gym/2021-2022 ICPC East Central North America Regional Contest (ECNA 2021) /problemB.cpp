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
int n, m;
int nxt[N];
int a[N];
int dp[1005];
int vis[1005];
int outdeg[N];
ll solve(int u) {
    if (u == -1) return 0;
    if (vis[u]) return dp[u];
    vis[u] = 1;
    return dp[u] = a[u] + solve(nxt[u]);
}

void test_case() {
    memset(nxt, -1, sizeof(nxt));
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        nxt[b] = a;
        outdeg[a]=1;

    }
    ll ans = 1e18;
    for (int i = 0; i < n; i++) {
        if(outdeg[i])continue;
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        int x = i;
        ll sm = 0;
        while (x != -1) {
            vis[x] = 1;
            sm += a[x];
            x = nxt[x];

        }
        for (int j = 0; j < n; j++) {
            if(j==i)continue;
            ll p = solve(j);
            if(outdeg[j]==0)
            ans = min(ans, sm+p);
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
