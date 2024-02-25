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

int n;
string s;
int a[N];
int ex[26];
int pos[26];
int dp[2][1024];
int freq[1024];
void test_case() {
    cin >> n;
    cin >> s;
    memset(freq, 0, sizeof(freq));
    memset(ex, 0, sizeof(ex));
    for (auto &c : s) {
        ex[c - 'a'] = 1;
    }
    int cnt = 0;
    for (int i = 0; i < 26; i++) {
        if (ex[i]) {
            pos[i] = cnt++;
        }
    }
    int tot = (1 << cnt) - 1;
    for (int i = 0; i < n; i++) {
        cin >> s;
        a[i] = 0;
        for (auto &c : s) {
            if (ex[c - 'a']) {
                a[i] ^= (1 << pos[c - 'a']);
            }
        }
        freq[a[i]]++;
    }
    for (int i = 1; i <= tot; i++) {
        dp[0][i] = -1e9;
    }
    dp[0][0] = freq[0];
    for (int i = 1; i <= tot; i++) {
        int id = i & 1;
        for (int j = 0; j <= tot; j++) {
            dp[id][j] = -1e9;
        }
        for (int j = 0; j <= tot; j++) {
            dp[id][j] = max(dp[id][j], dp[id ^ 1][j] + (freq[i] - freq[i] % 2));
        }
        if (freq[i] >= 1)
            for (int j = 0; j <= tot; j++) {
                dp[id][j ^ i] = max(dp[id][i ^ j], dp[id ^ 1][j] + (freq[i] - (1 - freq[i] % 2)));
            }
    }
    int ans = dp[tot & 1][tot];
    if (ans < 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
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
