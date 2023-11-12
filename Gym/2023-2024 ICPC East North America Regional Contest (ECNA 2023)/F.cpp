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

map<string, int> code;
string decode[N];
string mul2(string& a) {
    reverse(all(a));
    string rs = "";
    int r = 0;
    for (int i = 0; i < a.size(); i++) {
        r += 2 * (a[i] - '0');
        int x = r % 10;
        rs += char('0' + x);
        r = r / 10;
    }
    if (r) {
        rs += char('0' + r);
    }
    reverse(all(a));
    reverse(all(rs));
    return rs;
}

int a[N];
int n;
int dp[2][1005][205];

void test_case() {
    string cur = "1";
    code[cur] = 0;
    decode[0] = "1";
    for (int i = 1; i <= 200; i++) {
        cur = mul2(cur);
        code[cur] = i;
        decode[i] = cur;
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        a[i] = code[s];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 200; j++) {
            dp[0][i][j] = dp[0][i - 1][j];
        }
        int cur = a[i];
        int pos = i;

        while (pos > 0) {
            dp[0][i][cur] = max(pos, dp[0][i][cur]);
            pos = dp[0][pos - 1][cur];
            cur++;
        }
        for (int j = 0; j <= 200; j++) {
            if (dp[0][i][j] >= 1) {
                ans = max(ans, j);
            }
        }
    }
    cout << decode[ans] << endl;
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
