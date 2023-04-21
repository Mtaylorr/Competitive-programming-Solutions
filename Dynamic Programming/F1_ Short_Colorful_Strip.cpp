//https://codeforces.com/problemset/problem/1178/F1

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
const int MOD = 998244353;

int n, m;
int c[N];
int dp[505][505];
vector<int> v;

int solve(int l, int r) {
    if (r <= l) {
        return 1;
    }
    int &rs = dp[l][r];
    if (rs != -1) return rs;
    int lf = 0;
    int rg = 0;
    int mn = 1e9;
    int mnpos = 0;
    for (int i = l; i <= r; i++) {
        if (c[i] < mn) {
            mn = c[i];
            mnpos = i;
        }
    }
    for (int i = l; i <= mnpos; i++) {
        int x = solve(l, i - 1);
        int y = solve(i, mnpos - 1);
        lf = (lf + (x * 1ll * y) % MOD) % MOD;
    }
    for (int i = mnpos; i <= r; i++) {
        int x = solve(mnpos + 1, i);
        int y = solve(i + 1, r);
        rg = (rg + (x * 1ll * y) % MOD) % MOD;
    }
    rs = (lf * 1ll * rg) % MOD;
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    cout << solve(0, n - 1);
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
