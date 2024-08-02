// this shouldn't pass, theoretically it's o(n*q)
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

int n, q;
int t, l, r;
int dp[N], val[N];
int B;

void upd(int l, int r) {
    int lid = l / B;
    int rid = r / B;
    if (lid == rid) {
        for (int i = l; i <= r; i++) {
            val[i] = max(val[i], r);
        }
    } else {
        int lb = (lid + 1) * B - 1;
        for (int i = l; i <= lb; i++) {
            val[i] = max(val[i], r);
        }
        for (int bid = lid + 1; bid < rid; bid++) {
            dp[bid] = max(dp[bid], r);
        }
        int ub = rid * B;
        for (int i = ub; i <= r; i++) {
            val[i] = max(val[i], r);
        }
    }
}

int solve(int l, int r) {
    int cur = l;
    int ans = 0;
    while (cur <= r && cur != -1) {
        int bid = cur / B;
        int ub = min(n - 1, (bid + 1) * B - 1);
        if (val[cur] > dp[bid]) {
            ans += 1;
            cur = val[cur] + 1;
        } else if (dp[bid] >= val[cur] && dp[bid] != -1) {
            ans += 1;
            cur = dp[bid] + 1;
        } else {
            return -1;
        }
    }
    return ans;
}
void test_case() {
    memset(dp, -1, sizeof(dp));
    memset(val, -1, sizeof(val));
    cin >> n >> q;
    val[n] = n;
    B = sqrt(n);
    while (q--) {
        cin >> t >> l >> r;
        l--;
        r--;
        if (t == 1) {
            upd(l, r);
        } else {
            cout << solve(l, r) << endl;
        }
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
