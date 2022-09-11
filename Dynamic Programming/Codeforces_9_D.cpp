//https://codeforces.com/problemset/problem/9/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 1 << 17;
const int MOD =  1e9 +7  ;

ll dp[50][50][2];
int n,h;


ll solve(int cur, int rem, int st) {
    if (rem == 0) {
        if (st == 1 && cur < h + 1) {
            return 0;
        }
        if (st == 0 && cur >= h + 1)
            return 0;
        return 1;
    }
    if (dp[cur][rem][st] != -1) {
        return dp[cur][rem][st];
    }
    ll ans = 0;
    if (st == 0) {
        for (int j = 0; j <= rem - 1; j++) {
            ans += solve(cur + 1, j, 0) * solve(cur + 1, rem - 1 - j, 0);
        }
    } else {
        for (int j = 0; j <= rem - 1; j++) {
            ans += solve(cur + 1, j, 1) * solve(cur + 1, rem - 1 - j, 0);
            ans += solve(cur + 1, j, 0) * solve(cur + 1, rem - 1 - j, 1);
            ans += solve(cur + 1, j, 1) * solve(cur + 1, rem - 1 - j, 1);

        }
    }
    return dp[cur][rem][st] = ans;
}

int main() {
   // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp,-1, sizeof(dp));
    cin >> n >> h;
    cout << solve(1,n,1);

    return 0;
}
