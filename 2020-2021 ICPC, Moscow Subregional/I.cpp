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

int x, y;
int n;
int a[N];
ll dp[N][16];
ll F[N], G[N];
int pref[N];

int m;
int val[N];

ll solve(int p, int b) {
    if (p > m) {
        return 0;
    }
    if (b >= 16) {
        return 1e18;
    }
    ll &rs = dp[p][b];
    if (rs != -1) return rs;
    rs = 1e18;
    int cur = 1;
    for (int g = 0; g <= 4; g++) {
        int ub = p + cur - 1;
        ub = min(ub, m);
        rs = min(rs, (pref[ub] - pref[p - 1]) * 4 * g + solve(ub + 1, b + 1));
        cur = cur * 16;
        if (ub + 1 > m) break;
    }

    // dbg(p, b, rs);
    return rs;
}

void calcans(int p, int b) {
    if (p > m) {
        for (int i = b; i < 16; i++) {
            F[i] = 2e9 - x;
            G[i] = 0;
        }
        return;
    }
    ll &rs = dp[p][b];
    int cur = 1;
    int r = 0;

    for (int g = 0; g <= 4; g++) {
        int ub = p + cur - 1;
        ub = min(ub, m);
        if ((pref[ub] - pref[p - 1]) * 4 * g + solve(ub + 1, b + 1) == rs) {
            G[b] = g;
            F[b] = p;
            calcans(ub + 1, b + 1);
            return;
        }
        cur = cur * 16;
        r++;
        if (ub + 1 > m) break;
    }
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> x >> y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= x;
        pref[a[i]]++;
    }
    m = y - x;
    for (int i = 1; i <= m; i++) {
        pref[i] += pref[i - 1];
    }

    for (int i = 0; i <= m + 1; i++) {
        ll cur = 1;
        int r = 0;
        while (cur < (i + 1)) {
            cur *= 16;
            r++;
        }
        val[i] = r;
    }
    // dbg(val[1]);
    ll ans = 1e18;
    int p = 0;
    for (int i = 0; i <= m; i++) {
        int l = 0;
        int r = i;
        int cnt = pref[r];
        int g = val[r];

        if (g >= 5) break;

        ll rs = 4 * g * cnt + solve(r + 1, 1);
        if (ans > rs) {
            // dbg(rs);
            ans = rs;
            p = i;
        }
    }
    // dbg(ans);
    int cnt = pref[p];
    int g = val[p];
    F[0] = p - (1 << (4 * g)) + 1;
    G[0] = g;
    calcans(p + 1, 1);
    for (int i = 0; i < 16; i++) {
        cout << G[i] << " " << F[i] + x << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
