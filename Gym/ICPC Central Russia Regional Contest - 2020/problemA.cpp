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

int dpth[N];
int par[N];
vector<int> adj[N];
int dp[N];
int n, k;
void calc(int u) {
    dp[u] = 1;
    for (auto v : adj[u]) {
        dpth[v] = dpth[u] + 1;
        calc(v);
        dp[u] += dp[v];
    }
}

void dfs(int u, int &k) {
    if (!k) return;
    cout << u + 1 << " ";
    k--;
    for (auto v : adj[u]) {
        dfs(v, k);
    }
}
void test_case() {
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        par[i]--;
        adj[par[i]].pb(i);
    }
    calc(0);
    int mxd = -1;
    int ansu = -1;
    for (int i = 0; i < n; i++) {
        if (dp[i] >= k) {
            if (dpth[i] > mxd) {
                mxd = dpth[i];
                ansu = i;
            }
        }
    }
    if (ansu != -1)
        dfs(ansu, k);
    else {
        cout << -1 << endl;
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
