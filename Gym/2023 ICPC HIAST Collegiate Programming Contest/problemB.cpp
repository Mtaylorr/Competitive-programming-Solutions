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
const int N = 2e6 + 5;

const int P = 2e6 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int max_PF[P];
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
            max_PF[i] = i;

            for (int j = 2 * i; j <= ub; j += i) {
                max_PF[j] = i;
                is_prime[j] = 0;
            }
        }
    }

} nt;

const int LOGSPT = 21;
template <typename T>
class SPT {
   public:
    vector<T> spt[LOGSPT];
    int po[LOGSPT];
    vector<int> lg;
    int n;

    T mrg(T &x, T &y) { return min(x, y); }

    void init(vector<T> &v) {
        n = v.size();
        lg.assign(n + 1, 0);
        po[0] = 1;
        for (int i = 0; i < LOGSPT; i++) {
            spt[i].assign(n, 0);
            if (i > 0) po[i] = 2 * po[i - 1];
        }
        for (int i = 2; i <= n; i++) {
            lg[i] = 1 + lg[i / 2];
        }
        for (int i = 0; i < n; i++) {
            spt[0][i] = v[i];
        }
        for (int b = 1; po[b] <= n; b++) {
            for (int i = 0; i + po[b] <= n; i++) {
                spt[b][i] = max(spt[b - 1][i], spt[b - 1][i + po[b - 1]]);
            }
        }
    }
    T getLog(int l, int r) {
        int d = r - l + 1;
        T rs = 1e9;
        for (int i = LOGSPT - 1; i >= 0; i--) {
            if (po[i] <= d) {
                rs = mrg(rs, spt[i][l]);
                d -= po[i];
                l += po[i];
            }
        }
        return rs;
    }

    T get(int l, int r) {
        int lg2 = lg[r - l + 1];
        return max(spt[lg2][l], spt[lg2][r - po[lg2] + 1]);
    }
};
SPT<int> spt;

int a[N];
vector<int> b;
int tree[4 * N];
int n, q;

set<pair<int, int> > st;
void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id] = a[ns];
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    tree[id] = max(tree[l], tree[r]);
}
int get(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns > qe || qs > ne) return 0;
    if (qs <= ns && qe >= ne) return tree[id];
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return max(get(qs, qe, l, ns, md), get(qs, qe, r, md + 1, ne));
}
int cur = 0;
void upd(int curmx, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id] = tree[id] / nt.max_PF[tree[id]];
        b[ns] = ++cur;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    if (tree[l] == curmx) {
        upd(curmx, l, ns, md);
    }
    if (tree[r] == curmx) {
        upd(curmx, r, md + 1, ne);
    }
    tree[id] = max(tree[l], tree[r]);
}

void test_case() {
    cin >> n >> q;
    b.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build();
    while (tree[0] != 1) {
        upd(tree[0]);
    }
    spt.init(b);
    int l, r;
    while (q--) {
        cin >> l >> r;
        cout << spt.get(--l, --r) << "\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    nt.sieve(2e6);
    while (T--) {
        test_case();
    }
    return 0;
}
