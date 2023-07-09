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
int grid[105][105];
int sum[105][105];
int k;

int calc(int xs, int ys, int xe, int ye) {
    //dbg(sum[xe][ye], sum[xs - 1][ys - 1], sum[xe][ys - 1], sum[xs - 1][ye]);
    return sum[xe][ye] + sum[xs - 1][ys - 1] - sum[xe][ys - 1] -
           sum[xs - 1][ye];
}

void test_case() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            sum[i][j] =
                grid[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int o = 1; o <= i; o++) {
                int l = 0;
                int r = j;
                while (l < r) {
                    int md = (l + r + 1) / 2;
                    // dbg(md,calc(i - o, j - md, i, j));
                    if (calc(i - o + 1, j - md + 1, i, j) <= k) {
                        l = md;
                    } else {
                        r = md - 1;
                    }
                }
                ans = max(ans, o * l);
            }
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
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
