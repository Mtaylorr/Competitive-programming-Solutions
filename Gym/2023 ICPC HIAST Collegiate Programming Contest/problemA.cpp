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

ll dp[105][59050];
ll w[N];
ll msk[N];
int n;
ll solve(int p, int mask) {
    if (p >= n) return 0;
    ll &rs = dp[p][mask];
    if (rs != -1) return rs;
    rs = solve(p + 1, mask);
    if (msk[p] != -1) {
        bool cond = true;
        int nmask = mask;
        int x = msk[p];
        for (int j = 0; j <= 9; j++) {
            if ((nmask % 3) + (x % 3) >= 3) {
                cond = false;
            }
            nmask /= 3;
            x /= 3;
        }
        if (cond) {
            rs = max(rs, w[p] + solve(p + 1, mask + msk[p]));
        }
    }
    return rs;
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        memset(dp[i], -1, sizeof(dp[i]));
    }
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        map<int, int> freq;
        ll x = w[i];
        while (x) {
            freq[x % 10]++;
            x /= 10;
        }
        bool hasbigger = 0;
        ll cur = 1;
        msk[i] = 0;
        for (int j = 0; j <= 9; j++) {
            if (freq[j] >= 3) {
                msk[i] = -1;
                break;
            }
            msk[i] += cur * freq[j];
            cur *= 3;
        }
    }
    cout << solve(0, 0) << endl;
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
