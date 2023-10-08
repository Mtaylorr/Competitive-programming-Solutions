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

int n, m, k;
string s;
set<pair<int, int> > st;
int dp[1005][1005];
void test_case() {
    cin >> n >> m >> k;
    cin >> s;
    st.clear();
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    int x = 0;
    int y = 0;

    int lx = 1;
    int rx = n;
    int ly = 1;
    int ry = m;
    int a = 1, b = n, c = 1, d = m;
    for (auto &ca : s) {
        if (ca == 'U') {
            if (a == 1) {
                lx++;
            } else {
                a--;
            }
            b--;
            if (lx > rx || ly > ry) break;
            x--;
        } else if (ca == 'D') {
            if (b == n)
                rx--;
            else
                b++;
            a++;
            if (lx > rx || ly > ry) break;
            x++;
        } else if (ca == 'R') {
            if (d == m)
                ry--;
            else
                d++;
            c++;
            if (lx > rx || ly > ry) break;
            y++;
        } else if (ca == 'L') {
            if (c == 1)
                ly++;
            else
                c--;
            d--;
            if (lx > rx || ly > ry) break;
            y--;
        }
    }
    ll tot = n * m;
    if (lx <= rx && ly <= ry) {
        tot -= (rx - lx + 1) * (ry - ly + 1);
        dp[lx][ly]++;
        dp[rx + 1][ry + 1]++;
        dp[rx + 1][ly]--;
        dp[lx][ry + 1]--;
        st.insert({lx, ly});
        for (auto &c : s) {
            if (c == 'U') {
                rx--;
                lx--;
                x--;
            } else if (c == 'D') {
                lx++;
                rx++;
                x++;
            } else if (c == 'R') {
                ly++;
                ry++;
                y++;
            } else if (c == 'L') {
                ry--;
                ly--;
                y--;
            }
            if (st.count({lx, ly}) == 0) {
                dp[lx][ly]++;
                dp[rx + 1][ry + 1]++;
                dp[rx + 1][ly]--;
                dp[lx][ry + 1]--;
                st.insert({lx,ly});
            }
        }
    }
    int ans = 0;
    //dbg(tot);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            ans += (dp[i][j] + tot) == n * m - k;
            //dbg(i,j,dp[i][j]);
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
