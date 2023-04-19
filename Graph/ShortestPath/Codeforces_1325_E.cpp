//https://codeforces.com/problemset/problem/1325/E
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
const int N = 1e6 + 5;

int n, a[N];
set<int> adjset[N];
vector<int> adj[N];
int freq[N];
set<int> s;
vector<int> va;
int ans = 1e9;
int dist[N];
bool vis[N];
int par[N];

void bfs(int src) {
    for (auto x : va) {
        vis[x] = 0;
        dist[x] = 0;
    }
    queue<int> q;
    q.push(src);
    vis[src] = 1;
    dist[src] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &v : adj[u]) {
            if (vis[v]) {
                if (par[u] != v) {
                    ans = min(ans, dist[v] + dist[u] + 1);
                }
            } else {
                vis[v] = 1;
                par[v] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

void addEdge(int x, int y) {
    s.insert(x);
    s.insert(y);

    if (adjset[x].count(y) == 0) {
        adj[x].pb(y);
    }
    if (adjset[y].count(x) == 0) {
        adj[y].pb(x);
    }
    adjset[x].insert(y);
    adjset[y].insert(x);
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vector<int> tmp;
        for (int j = 2; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                int nb = 0;
                while (a[i] % j == 0) {
                    a[i] /= j;
                    nb++;
                }
                if (nb % 2) {
                    tmp.pb(j);
                }
            }
        }
        if (a[i] > 1) {
            tmp.pb(a[i]);
        }
        a[i] = 1;
        for (auto u : tmp) {
            a[i] *= u;
        }
        if (a[i] == 1) {
            cout << 1;
            return;
        }
        if (tmp.size() == 2) {
            addEdge(tmp[0], tmp[1]);
        } else {
            addEdge(1, tmp[0]);
        }
        freq[a[i]]++;
    }
    for (int i = 1; i <= 1e6; i++) {
        if (freq[i] >= 2) {
            cout << 2 << endl;
            return;
        }
    }

    for (auto &u : s) {
        va.pb(u);
    }
    for (int i = 1; i <= 1e3; i++) {
        if (adj[i].size() == 0) continue;
        bfs(i);
    }
    if (ans < 1e9) {
        cout << ans << endl;
    } else {
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
