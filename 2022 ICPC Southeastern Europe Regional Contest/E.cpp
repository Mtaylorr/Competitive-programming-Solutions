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
int a[N];

map<int, ll> dp[N];
vector<pair<int, int> > v;

ll solve(int p, int bef = -1) {
    if (p >= n) return 0;
    if (dp[p].count(bef)) return dp[p][bef];
    ll sm = 1e18;
    int l = 2 * p;
    int r = l + 1;
    ll ans = 1e18;
    if (v[l].se != v[r].se) {
        ans = min(ans, v[r].fi - v[l].fi + solve(p + 1, r));
    } else {
        if (bef != -1)
            ans = min(ans, v[r].fi + v[l].fi - 2 * v[bef].fi + solve(p + 1, r));
        if (p + 1 < n) {
            ans = min(ans, v[r + 1].fi - v[l].fi + v[r + 2].fi - v[r].fi +
                               solve(p + 2, r + 2));
        }
    }
    return dp[p][bef] = ans;
}
void test_case() {
    cin >> n;

    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
        v.pb({a[i], i / 2});
    }
    sort(all(v));
    ll ans = solve(0);

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
