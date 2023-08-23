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

/*
2
5 1 10
4 2 7
*/

int n;
ll l, r;
int freq[3005];
int dp[2][3005];
int cur[2][3005];
void solve(int m) {
    for (int i = 0; i <= n; i++) {
        cur[0][i] = 0;
    }
    cur[0][0] = 1;
    for(int i=0;i<n;i++){
        dp[0][i]=freq[i];
    }
    while (m) {
        if (m % 2) {
            for (int i = 0; i < n; i++) {
                cur[1][i] = 0;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int k = (i + j) % n;
                    cur[1][k] =
                        (cur[1][k] + (cur[0][i] * 1ll * dp[0][j]) % MOD) % MOD;
                }
            }
            for (int i = 0; i < n; i++) {
                cur[0][i] = cur[1][i];
            }
        }
        m /= 2;
        for (int i = 0; i < n; i++) {
            dp[1][i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int k = (i + j) % n;
                dp[1][k] = (dp[1][k] + (dp[0][i] * 1ll * dp[0][j]) % MOD) % MOD;
            }
        }
        for (int i = 0; i < n; i++) {
            dp[0][i] = dp[1][i];
        }
    }
}
void test_case() {
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++) {
        int lf = l - l % n;
        lf += i;
        if (lf < l) lf += n;
        int rg = r - r % n;
        rg += i;
        if (rg > r) rg -= n;
        freq[i] = 0;
        if (lf <= rg) {
            freq[i] = (rg - lf) / n + 1;
        }
    }
    solve(n);
    cout << cur[0][0] << endl;
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
