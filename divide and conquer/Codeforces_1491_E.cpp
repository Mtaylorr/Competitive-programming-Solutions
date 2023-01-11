//https://codeforces.com/problemset/problem/1491/E

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

set<int> s;
set<int> fibs;
set<int> adj[N];
int dp[N];
int n;
bool cond = true;

void calcsz(int u, int p = -1) {
    dp[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        calcsz(v, u);
        dp[u] += dp[v];
    }
}

void findcut(int u, int p, int s, int &x, int &y) {
    if (x != -1) return;
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (x != -1) return;
        if (fibs.count(dp[v]) && fibs.count(s - dp[v])) {
            x = u;
            y = v;
            return;
        }
        findcut(v, u, s, x, y);
    }
}

void process(int u) {
    if (!cond) return;
    calcsz(u);
    int m = dp[u];
    if (m == 1) {
        return;
    }
    if (fibs.count(m) == 0) {
        cond = 0;
    }
    int x = -1, y = -1;
    findcut(u, -1, m, x, y);
    if (x == -1) {
        cond = 0;
    }
    adj[x].erase(y);
    adj[y].erase(x);
    process(x);
    process(y);
}

void test_case() {
    fibs.insert(1);
    cin >> n;
    int u0 = 1;
    int u1 = 1;
    while (1) {
        int u2 = u0 + u1;
        if (u2 > n) break;
        fibs.insert(u2);
        u0 = u1;
        u1 = u2;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    process(0);
    if (cond) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
