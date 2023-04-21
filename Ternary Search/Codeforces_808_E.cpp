//https://codeforces.com/problemset/problem/808/E
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
int n, m;
vector<int> cst[4];
ll sum[4][N];

ll sum1(int x) {
    x = min(x, (int)cst[1].size());
    return x > 0 ? sum[1][x - 1] : 0;
}

ll solve(ll x, int m) {
    int remm = m - x * 2;
    if (remm < 0) return -1e17;
    ll cs = x > 0 ? sum[2][x - 1] : 0;
    return cs + sum1(remm);
}

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cst[x].pb(y);
    }
    for (int i = 1; i <= 3; i++) {
        sort(rall(cst[i]));
        ll s = 0;
        for (int j = 0; j < cst[i].size(); j++) {
            s += cst[i][j];
            sum[i][j] = s;
        }
    }
    ll ans = 0;
    for (int i = 0; i <= cst[3].size();i++) {
        int remm = m - 3 * i;
        ll cs = i > 0 ? sum[3][i - 1] : 0;
        if (remm < 0) break;
        int l = 0;
        int r = cst[2].size();
        while (r - l >= 3) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            ll v1 = solve(m1, remm);
            ll v2 = solve(m2, remm);
            if (v1 >= v2) {
                r = m2;
            } else {
                l = m1;
            }
        }
        for (int j = l; j <= r; j++) {
            ans = max(ans, cs + solve(j, remm));
        }
    }
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
