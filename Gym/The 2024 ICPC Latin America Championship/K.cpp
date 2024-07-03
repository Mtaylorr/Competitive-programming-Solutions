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
const int N = 1e6 + 5;

bool isVowel[26];
int n;
string s[N];
int dp[N][2][2];

int solve(int p, int c0, int c1) {
    if (p >= n) return 0;
    int &rs = dp[p][c0][c1];
    if (rs != -1) return rs;
    rs = 1e9;
    string &cur = s[p];
    int b0 = c0;
    int b1 = c1;
    for (int i = 0; i < min((int)cur.size(), 3); i++) {
        if (b1 == 0 || b0 == 0 || isVowel[cur[i] - 'A']) {
            rs = min(rs, i + 1 + solve(p + 1, b1, !isVowel[cur[i] - 'A']));
        }
        if (b1 == 1 && b0 == 1 && !isVowel[cur[i] - 'A']) break;
        b0 = b1;
        b1 = !isVowel[cur[i] - 'A'];
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    isVowel['A' - 'A'] = isVowel['E' - 'A'] = isVowel['I' - 'A'] = isVowel['O' - 'A'] = isVowel['U' - 'A'] = isVowel['Y' - 'A'] = 1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int ans = solve(0, 0, 0);
    if (ans <= 1e6) {
        cout << ans << endl;
    } else {
        cout << "*" << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
