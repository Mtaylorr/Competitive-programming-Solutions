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

int n, k;
int t[N];
int dp[1 << 10][1442][11];

int solve(int msk, int md, int nb, int rem) {
    if (nb == 0) return md == 0;
    if (msk == (1 << n) - 1) return 0;
    int& rs = dp[msk][md][nb];
    if (rs != -1) return rs;
    rs = 0;
    for (int i = 0; i < n; i++) {
        if (((1 << i) & msk)) continue;
        if (rem < t[i]) continue;
        rs = max(rs, solve(msk + (1 << i), (md + 1440 - (k - rem+t[i])) % 1440,
                           nb - 1, rem - t[i]));
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> k >> n;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    for (int i = 10; i >= 0; i--) {
        for (int j = 0; j < 1440; j++) {
            if (solve(0, j, i, k)) {
                cout << i << " " << j << endl;
                return;
            }
        }
    }
    cout << 0 << " " << 0 << endl;
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
