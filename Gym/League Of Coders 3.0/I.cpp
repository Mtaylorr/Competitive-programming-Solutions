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

ll dp[1 << 22];
ll sum[1 << 22];
ll pref[N];
int n, m;
int a[N];
int p[N], b[N];

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = a[i];
        if (i > 0) {
            pref[i] += pref[i - 1];
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    for (int j = 0; j < (1 << m); j++) {
        for (int i = 0; i < m; i++) {
            if ((1 << i) & j) {
                sum[j] += p[i];
            }
        }
    }
    ll ans = -1e18;
    dp[0] = 0;
    for (int msk = 1; msk < (1 << m); msk++) {
        dp[msk] = -1e18;
        int id = -1;
        for (int j = 0; j < n; j++) {
            if (pref[j] >= sum[msk]) {
                id = j;
                break;
            }
        }
        if (id == -1) continue;
        ll used = sum[msk] - (pref[id] - a[id]);
        for (int i = 0; i < m; i++) {
            if (((1 << i) & msk) && used >= p[i]) {
                dp[msk] = max(dp[msk], dp[msk ^ (1 << i)] + b[i]);
            }
        }
        if (sum[msk] == pref[id] && id == n - 1) {
            ans = max(ans, dp[msk]);
        }
    }
    if (ans > 0) {
        cout << ans << endl;
    } else {
        cout << 0 << endl;
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
