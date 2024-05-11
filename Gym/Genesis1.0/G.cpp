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
int n;
ll a[N], k;

ll dp[N][20];
vector<int> primes;

ll solve(int p, int msk) {
    if (p >= n) {
        if(msk == (1 << primes.size()) - 1)return 0;
        return 1e18;
    }
    ll &rs = dp[p][msk];
    if (rs != -1) return rs;
    rs = 1e18;
    for (int m = 0; m < (1 << primes.size()); m++) {
        ll c = 1;
        for (int i = 0; i < primes.size(); i++) {
            if ((1 << i) & m) {
                c *= primes[i];
            }
        }
        ll diff = (c - a[p] % c) % c;
        rs = min(rs, diff + solve(p + 1, msk | m));
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    ll mn = 1e18;

    for (int i = 2; i * i <= k; i++) {
        while (k % i == 0) {
            primes.pb(i);
            k /= i;
        }
    }
    if (k > 1) {
        primes.pb(k);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << solve(0, 0) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
