//https://codeforces.com/problemset/problem/351/B
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
const int N = 4500000 +5 ;

bool vis[2][N];
float dp[2][N];
int a[N];
int n;

float calc(int p, int g) {
    if (p == 0) {
        return 0;
    }
    if (vis[g][p]) return dp[g][p];
    vis[g][p]=1;
    double rs = 0;
    if (p == (n * (n - 1)) / 2) {
        return dp[g][p] = 1 + calc(p - 1, 1 - g);
    }
    if (g == 0) {
        return dp[g][p] = 1+calc(p - 1, 1 - g);
    } else {
        dp[g][p] = 3 + calc(p - 1, 1-g);
    }
    return dp[g][p];
}

void solve() {
    cin >> n;
    int p = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < i; j++) {
            if (a[j] > a[i]) {
                p++;
            }
        }
    }
    float ans = calc(p, 0);
    cout << fixed << setprecision(10) << ans;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    //cin >> T;
    T=1;
    while (T--) {
        solve();
    }
    return 0;
}
