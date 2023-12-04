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
const int N = 2e6 + 5;
int n;
int c;
int d[N];
int dp[N];
int roots[N];
int par[N][21];

void test_case() {
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        d[i + n] = d[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        d[i] += d[i - 1];
    }
    for (int j = 0; j <= 20; j++) {
        par[2 * n + 1][j] = 2 * n + 1;
    }
    for (int i = 2 * n; i >= 1; i--) {
        int nx;
        int l = i;
        int r = min(2 * n, i + n - 1);
        while (l < r) {
            int md = (l + r) / 2;
            ll s = d[md] - d[i - 1];
            if (s < c) {
                l = md + 1;
            } else {
                r = md;
            }
        }
        ll s = d[l] - d[i - 1];
        if (s < c || l + 1 > 2 * n || l + 1 >= i + n) {
            for (int j = 0; j <= 20; j++) {
                par[i][j] = 2 * n + 1;
            }
        } else {
            par[i][0] = l + 1;
            for (int j = 1; j <= 20; j++) {
                par[i][j] = par[par[i][j - 1]][j - 1];
            }
        }
        dp[i] = 0;
        int p = i;
        for (int j = 20; j >= 0; j--) {
            if (par[p][j] <= i + n - 1 && par[p][j] <= 2 * n) {
                dp[i] += (1 << j);
                p = par[p][j];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << " ";
    }
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
