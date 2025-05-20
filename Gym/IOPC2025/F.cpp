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

const int E = 1e6 + 5;

#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E];

    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }

    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

int n;

bool ans = false;

int dp[N];
int dpsz[N];

void solve(int u, int p = -1) {
    dpsz[u] = 1;
    neig(u, v, e, adj) {
        if (v == p) continue;
        solve(v, u);
        dpsz[u] += dpsz[v];
        if (dp[u] != -1 && dp[v] != -1 && n - dp[u] - dp[v] >= 3) {
            ans = true;
        }
        if (dp[u] == -1) {
            dp[u] = dp[v];
        } else if (dp[v] != -1) {
            dp[u] = min(dp[u], dp[v]);
        }
    }
    neig(u, v, e, adj) {
        if (v == p) continue;

        if (dp[v] != -1 && (dpsz[u] - dp[v]) % 2 == 1 && dpsz[u] - dp[v] >= 3 && n - dpsz[u] >= 3 && (n - dpsz[u]) % 2 == 1) {
            ans = true;
        }
    }
    if (dp[u] == -1 && dpsz[u] % 2 == 1 && dpsz[u] >= 3) {
        dp[u] = dpsz[u];
    }
}
void test_case() {
    cin >> n;
    adj.init(n);
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    if (n % 2 == 0) {
        cout << "NO\n";
        return;
    }
    solve(0);
    if (ans) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
