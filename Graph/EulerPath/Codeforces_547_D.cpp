//https://codeforces.com/contest/547/problem/D
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
const int N = 4e5 + 5;

int n, x[N], y[N];
set<int> adj[N];
int cnt[N][2];
int deg[N];
vector<int> removed;
set<int> odds;
bool vis[N];
int col[N];
bool done[N];
vector<int> ord;

map<pair<int, int>, int> pos;

void dfs(int u, int p = -1) {
    int v;
    while (adj[u].size()) {
        v = *adj[u].begin();
        adj[u].erase(adj[u].begin());
        if (vis[v]) continue;
        vis[v] = 1;
        int nx = x[v] + y[v] - u;
        dfs(nx, v);
    }
    if (p != -1) ord.pb(p);
}

pair<int, int> getpair(int a, int b) { return {min(a, b), max(a, b)}; }

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        y[i] += 2e5;
        adj[x[i]].insert(i);
        adj[y[i]].insert(i);
        deg[x[i]]++;
        deg[y[i]]++;
        pos[{x[i], y[i]}] = i;
    }
    for (int i = 1; i <= 4e5; i++) {
        if (deg[i] % 2) {
            odds.insert(i);
        }
    }
    while (odds.size()) {
        int u = *odds.begin();
        odds.erase(odds.begin());
        if (deg[u] % 2 == 0) continue;
        int v = *adj[u].begin();
        removed.pb(v);
        deg[x[v]]--;
        deg[y[v]]--;
        adj[x[v]].erase(v);
        adj[y[v]].erase(v);
        if (deg[x[v]] % 2) {
            odds.insert(x[v]);
        }
        if (deg[y[v]] % 2) {
            odds.insert(y[v]);
        }
    }
    for (int i = 1; i <= 4e5; i++) {
        if (done[i]) continue;
        ord.clear();
        dfs(i);
        if (sz(ord) >= 1) {
            for (int j = 0; j < sz(ord); j++) {
                int u = ord[j];
                col[u] = j % 2;
                cnt[x[u]][col[u]]++;
                cnt[y[u]][col[u]]++;
            }
        }
    }
    while (removed.size()) {
        int u = removed.back();
        removed.pop_back();
        if (cnt[x[u]][0] != cnt[x[u]][1]) {
            if (cnt[x[u]][0] < cnt[x[u]][1]) {
                col[u] = 0;
                cnt[x[u]][0]++;
                cnt[y[u]][0]++;
            } else {
                col[u] = 1;
                cnt[x[u]][1]++;
                cnt[y[u]][1]++;
            }
        } else {
            if (cnt[y[u]][0] < cnt[y[u]][1]) {
                col[u] = 0;
                cnt[x[u]][0]++;
                cnt[y[u]][0]++;
            } else {
                col[u] = 1;
                cnt[x[u]][1]++;
                cnt[y[u]][1]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "br"[col[i]];
    }
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
