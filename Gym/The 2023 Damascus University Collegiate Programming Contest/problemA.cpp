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

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

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
map<int, int> freq;
int a[N], b[N];
int n;
vector<int> pos[N];
bool vis[N];
int cnt0, cnt1;
bool cond = 0;
bool col[N];

void dfs(int u, int p = -1, int c = 0) {
    col[u] = c;
    cnt0 += c == 0;
    cnt1 += c == 1;
    vis[u] = 1;
    neig(u, v, e, adj) {
        if (vis[v]) {
            if (col[v] != (col[u] + adj.cst[e]) % 2) {
                cond = false;
            }
            continue;
        }
        dfs(v, u, (c + adj.cst[e])%2);
    }
}
void test_case() {
    freq.clear();
    cin >> n;
    adj.init(n);
    for (int i = 0; i <= 2 * n; i++) {
        pos[i].clear();
    }
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
        cin >> a[i] >> b[i];
        freq[a[i]]++;
        pos[a[i]].pb(i);
        freq[b[i]]++;
        pos[b[i]].pb(i);
    }

    for (auto u : freq) {
        if (u.se > 2) {
            cout << -1 << endl;
            return;
        }
    }
    for (int i = 0; i <= 2 * n; i++) {
        if (pos[i].size() <= 1) continue;
        int x = pos[i][0];
        int y = pos[i][1];
        if (x == y) continue;
        if (a[x] == i && a[y] == i) {
            adj.addBiEdge(x, y, 1);
        } else if (b[x] == i && b[y] == i) {
            adj.addBiEdge(x, y, 1);
        } else {
            adj.addBiEdge(x, y, 0);
        }
    }
    int ans = 0;
    cond = true;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        cnt0 = cnt1 = 0;
        dfs(i);
        if (!cond) {
            cout << -1 << endl;
            return;
        }
        ans += min(cnt0, cnt1);
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
