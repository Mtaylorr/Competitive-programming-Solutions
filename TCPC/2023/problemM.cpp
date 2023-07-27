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
const int MOD = 1e9 + 7;

int id[N];
int getid(int u) { return id[u] == u ? u : id[u] = getid(id[u]); }

void uni(int u, int v) {
    u = getid(u);
    v = getid(v);
    id[u] = v;
}

void init(int n) {
    for (int i = 0; i < n; i++) {
        id[i] = i;
    }
}
string s;
int n, k;
map<int, vector<int> > tmp;
vector<vector<int> > comps[205];
int dp[205][205];

int calc(int p, int b) {
    int rs = 1;
    for (auto &u : comps[b]) {
        set<int> st;
        bool hasrandom = 0;
        for (auto &v : u) {
            int x = (v + p) % n;
            if (s[x] == '?') {
                hasrandom = 1;
            } else {
                st.insert(s[x] - 'a');
            }
        }
        if (st.size() >= 2) return 0;
        if (st.size() == 0) {
            rs = (rs * 1ll * 26);
        }
    }
    return rs;
}

int solve(int p, int s) {
    if (p > k) return 0;
    int &rs = dp[p][s];
    if (rs != -1) return rs;
    rs = calc(p, s);
    for (int i = p + 1; i <= k; i++) {
        rs = (rs + 0ll + MOD - solve(i, __gcd(i - p, s)));
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    cin >> s;
    for (int j = 0; j <= k; j++) {
        tmp.clear();
        init(n);
        for (int i = 0; i < n; i++) {
            uni(i, n - 1 - i);
            int x = ((n - 1 - (i + n - j) % n) + j) % n;
            uni(i, x);
        }
        for (int i = 0; i < n; i++) {
            tmp[getid(i)].pb(i);
        }
        for (auto &u : tmp) {
            comps[j].pb(u.se);
        }
    }
    int ans = 0;
    for (int i = 0; i <= k; i++) {
        ans = (ans + solve(i, 0)) % MOD;
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
