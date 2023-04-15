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

ll n;
int dp[N][3][3];
map<char, int> code;
string s;

int solve(int p, int b, int st) {
    if (p >= n) {
        if (b != st) {
            return 0;
        } else {
            return 1e9;
        }
    }
    int &rs = dp[p][b][st];
    if (rs != -1) return rs;
    rs = 1e9;
    for (int i = 0; i < 3; i++) {
        if (i == b) continue;
        rs = min(rs, (code[s[p]] != i) + solve(p + 1, i, st));
    }
    return rs;
}

void test_case() {
    code['S'] = 0;
    code['P'] = 1;
    code['R'] = 2;
    cin >> s;
    n = s.size();
    for (int i = 0; i <= n; i++) {
        memset(dp[i], -1, sizeof(dp[i]));
    }
    int ans = 1e9;
    for (int i = 0; i < 3; i++) {
        int rs = (i != code[s[0]]) + solve(1, i, i);
        ans = min(ans, rs);
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
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
