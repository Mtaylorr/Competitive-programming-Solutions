//https://codeforces.com/contest/1442/problem/D
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
vector<ll> a[3005];
ll ans = 0;

void upd(vector<ll> &tmp, int num, ll sum) {
    for (int j = tmp.size() - num - 1; j >= 0; j--) {
        tmp[j + num] = max(tmp[j + num], tmp[j] + sum);
    }
}

void calc(int ns, int ne, const vector<ll> &dp) {
    if (ns == ne) {
        for (int i = 0; i <= k; i++) {
            if (k - i < a[ns].size()) {
                ans = max(ans, a[ns][k - i] + dp[i]);
            }
        }
        return;
    }

    {
        vector<ll> tmp = dp;
        int md = (ne + ns) / 2;
        for (int i = ns; i <= md; i++) {
            upd(tmp, a[i].size() - 1, a[i].back());
        }
        calc(md + 1, ne, tmp);
    }
    {
        vector<ll> tmp = dp;
        int md = (ne + ns) / 2;
        for (int i = md + 1; i <= ne; i++) {
            upd(tmp, a[i].size() - 1, a[i].back());
        }
        calc(ns, md, tmp);
    }
}

void test_case() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        a[i].resize(t + 1);
        a[i][0] = 0;
        for (int j = 1; j <= t; j++) {
            cin >> a[i][j];
            a[i][j] += a[i][j - 1];
        }
    }
    vector<ll> dp(k + 1, 0);
    dp[0] = 0;
    calc(0, n - 1, dp);
    cout << ans << endl;
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
