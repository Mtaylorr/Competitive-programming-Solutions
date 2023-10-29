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
pair<int, int> tree[4 * N];

int n, q;
int dpth[N];
int tin[N], tout[N];
int ti = -1;
vector<int> itd;
void dfs(int u, int p = -1) {
    tin[u] = ++ti;
    itd.pb(u);
    for (auto& v : adj[u]) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
    }
    tout[u] = ti;
}

void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id] = {1e9, 0};
        return;
    }

    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    tree[id] = min(tree[l], tree[r]);
}
void upd(int p, int v, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id].se += v;
        if (tree[id].se) {
            tree[id].fi = dpth[itd[ns]];
        } else {
            tree[id].fi = 1e9;
        }
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    if (p <= md)
        upd(p, v, l, ns, md);
    else
        upd(p, v, r, md + 1, ne);
    tree[id] = min(tree[l], tree[r]);
}

int getFirst(int qs, int qe, int v, int id = 0, int ns = 0, int ne = n - 1) {
    if (qs > ne || ns > qe) return -1;
    if (tree[id].fi > v) return -1;
    if (ns == ne) {
        return itd[ns];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    int p = getFirst(qs, qe, v, l, ns, md);
    if (p == -1) {
        p = getFirst(qs, qe, v, r, md + 1, ne);
    }
    return p;
}

const int P = 2e6 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int sieve_size;

    NumberTheory() { sieve_size = 0; }
    template <typename T>
    T gcd(T a, T b) {
        return (b == 0 ? a : gcd(b, a % b));
    }
    template <typename T>
    T lcm(T a, T b) {
        return a * (b / gcd(a, b));
    }
    template <typename T>
    bool issquare(T w) {
        T sq = round(sqrt(w));
        return sq * sq == w;
    }
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
    template <typename T>
    T EulerPhi(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        T ans = N;
        while (primes.size() && N != 1 && (PF * 1ll * PF <= N)) {
            if (N % PF == 0) ans -= ans / PF;
            while (N % PF == 0) N /= PF;
            PF = primes[++PF_idx];
        }
        if (N != 1) ans -= ans / N;
        return ans;
    }

} nt;

int ty[N], l[N], r[N], v[N];
int ans[N];
vector<int> upds[N];
void test_case() {
    nt.sieve(1000000);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs(0);
    build();
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> ty[i];
        if (ty[i] == 1) {
            cin >> v[i] >> l[i] >> r[i];
            --v[i];
        } else {
            cin >> v[i];
            --v[i];
        }
    }
    for (int i = q - 1; i >= 0; i--) {
        if (ty[i] == 2) {
            upds[v[i]].pb(i);
            upd(tin[v[i]], 1);
        } else {
            while (1) {
                int a =
                    getFirst(tin[v[i]], tout[v[i]], dpth[v[i]] + r[i] - l[i]);
                if (a == -1) break;
                upd(tin[a], -1);
                int d = dpth[a] - dpth[v[i]];
                int x = upds[a].back();
                upds[a].pop_back();
                ans[x] = nt.EulerPhi(l[i] + d);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        if (ty[i] == 2) {
            cout << ans[i] << "\n";
        }
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
