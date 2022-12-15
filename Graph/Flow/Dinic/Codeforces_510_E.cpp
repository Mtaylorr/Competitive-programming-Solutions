//https://codeforces.com/problemset/problem/510/E
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

const int E = 2e6 + 5;

#define neig(u, e, v) \
    for (int e = head[u], v; (~e) && (v = to[e], 1); e = nxt[e])
#define neigd(u, e, v, d) \
    for (int e = d.head[u], v; (~e) && (v = d.to[e], 1); e = d.nxt[e])
template <typename T>
struct Dinic {
    int head[N], nxt[E], to[E], edgcnt = 0, n, work[N];
    T cap[E];
    int vis[N], vid = 0, dist[N], par[N], src, snk;

    void addEdge(int a, int b, T c) {
        nxt[edgcnt] = head[a];
        to[edgcnt] = b;
        cap[edgcnt] = c;
        head[a] = edgcnt++;
    }

    void addAug(int a, int b, T fcp, T rcp = 0) {
        addEdge(a, b, fcp);
        addEdge(b, a, rcp);
    }

    void init() {
        memset(head, -1, n * sizeof(head[0]));
        memset(vis, 0, n * sizeof(vis[0]));
        edgcnt = 0;
    }
    bool bfs() {
        queue<int> q;
        dist[src] = 0;
        vis[src] = ++vid;
        q.push(src);
        while (q.size()) {
            int u = q.front();
            q.pop();
            neig(u, e, v) {
                if (!cap[e] || vis[v] == vid) continue;
                dist[v] = dist[u] + 1;
                vis[v] = vid;
                q.push(v);
            }
        }
        return vis[snk] == vid;
    }

    T dfs(int u, T fl = INT_MAX) {
        if (u == snk) return fl;

        for (int &e = work[u], v; (~e) && (v = to[e], 1); e = nxt[e]) {
            if (!cap[e] || dist[v] != dist[u] + 1) continue;
            T f = dfs(v, min(cap[e], fl));
            if (f) {
                cap[e] -= f;
                cap[e ^ 1] += f;
                return f;
            }
        }
        return 0;
    }

    T dinic() {
        T flow = 0, f = 0;
        while (bfs()) {
            memcpy(work, head, n * sizeof(head[0]));
            do {
                f = dfs(src);
                flow += f;
            } while (f);
        }
        return flow;
    }
};

const int P = 1e5 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int sieve_size;
    void sieve(int ub) {
        sieve_size = ub;
        primes.clear();
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            primes.pb(i);
            if (i * 1ll * i <= ub)
                for (int j = i * i; j <= ub; j += i) {
                    is_prime[j] = 0;
                }
        }
    }

} nt;

Dinic<int> dinic;
int n, a[N];
vector<vector<int> > ans;
vector<int> tmp;
int nxt[N], hasNext[N];
bool vis[N];
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    tmp.pb(u);
    neigd(u, e, v, dinic) {
        if (a[u] % 2 == 0) {
            if (vis[v] || dinic.cap[e] == 1 || v >= n) continue;
            dfs(v);
            break;
        } else {
            if (vis[v] || dinic.cap[e] == 0 || v >= n) continue;
            dfs(v);
            break;
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        nxt[i] = hasNext[i] = -1;
    }
    dinic.n = n + 2;
    dinic.src = dinic.n - 1;
    dinic.snk = dinic.n - 2;
    dinic.init();
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            dinic.addAug(dinic.src, i, 2);
        } else {
            dinic.addAug(i, dinic.snk, 2);
        }
        for (int j = i + 1; j < n; j++) {
            int x = a[i] + a[j];
            if (nt.is_prime[x]) {
                if (a[i] % 2 == 0) {
                    dinic.addAug(i, j, 1);
                } else {
                    dinic.addAug(j, i, 1);
                }
            }
        }
    }
    int rs = dinic.dinic();
    if (rs != n) {
        cout << "Impossible";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        tmp.clear();
        dfs(i);
        ans.pb(tmp);
    }
    cout << ans.size() << endl;
    for (auto &u : ans) {
        cout << sz(u) << " ";
        for (auto v : u) {
            cout << v + 1 << " ";
        }
        cout << "\n";
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
    nt.sieve(1e5);
    while (T--) {
        solve();
    }
    return 0;
}
