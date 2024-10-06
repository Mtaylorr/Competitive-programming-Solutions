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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }

const int MOD = 998244353;

int sum[1 << 24];
int dp[1 << 24];
int n, m;
int a, b, c;

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        --a, --b, --c;
        a = 1 << a;
        b = 1 << b;
        c = 1 << c;
        sum[a + c]++;
        sum[a + b + c]--;
    }
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) {
                sum[mask] += sum[mask ^ (1 << i)];
            }
        }
    }
    dp[0] = 1;
    int tot = (1 << n) - 1;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (sum[mask] || sum[tot ^ mask]) continue;
        // dbg(mask, sum[mask], sum[mask ^ tot]);
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                int nmask = mask ^ (1 << i);
                if (sum[nmask] || sum[nmask ^ tot]) continue;
                dp[mask] = (dp[mask] + dp[nmask]) % MOD;
            }
        }
    }
    cout << dp[tot];
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
