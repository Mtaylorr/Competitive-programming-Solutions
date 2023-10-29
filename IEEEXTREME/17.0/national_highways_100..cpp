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

struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;

map<string, int> code;
int m = 0;
vector<int> ord;
int u[N], v[N], w[N];

string a, b;
int n;
int getcode(string &s) {
    if (code.count(s)) {
        return code[s];
    }
    code[s] = m++;
    return code[s];
}

vector<int> so[N];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> w[i];
        u[i] = getcode(a);
        v[i] = getcode(b);
        ord.pb(i);
        so[w[i]].pb(i);
    }
    dsu.init(m);
    ll ans = 0;
    for (int i = 0; i <= 1e6; i++) {
        for (auto idx : so[i]) {
            if (!dsu.sameSet(u[idx], v[idx])) {
                ans += i;
            }
        }
        for (auto idx : so[i]) {
            dsu.uni(u[idx], v[idx]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (!dsu.sameSet(i, 0)) {
            cout << "-1\n";
            return;
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
