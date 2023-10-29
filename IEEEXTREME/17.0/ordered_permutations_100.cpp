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

ll dp[2][8005];
ll dpsum[2][8005];
int n;
string s;
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        dp[0][i] = 1;
        dpsum[0][i] = (i + 1);
    }
    cin >> s;
    for (int i = 1; i < n; i++) {
        int id = i & 1;
        int gt = s[i - 1] == '<';
        int rem = n - i - 1;
        for (int j = 0; j <= rem; j++) {
            dpsum[id][j] = 0;
            dp[id][j] = 0;
            if (gt) {
                dp[id][j] = (dp[id][j] + dpsum[id ^ 1][j]) % MOD;
            } else {
                dp[id][j] = (dp[id][j] + dpsum[id ^ 1][rem + 1] + 0ll + MOD -
                             dpsum[id ^ 1][j]) %
                            MOD;
            }
            dpsum[id][j] = (dpsum[id][j] + dp[id][j]) % MOD;
            if (j > 0) {
                dpsum[id][j] = (dpsum[id][j] + dpsum[id][j - 1]) % MOD;
            }
        }
    }
    cout << dp[(n - 1) & 1][0] << endl;
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
