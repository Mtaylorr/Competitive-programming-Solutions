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

int dp[1005][1005];
int st[N];
int en[N];
int freq[N];
int a[N];
int n;
void test_case() {
    memset(st, -1, sizeof(st));
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        sum = 0;
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) dp[i][j] = sum + 2;
            if (st[a[j]] != -1) {
                sum -= dp[st[a[j]]][en[a[j]]];
            }
            if (st[a[j]] == -1) {
                st[a[j]] = j;
            }
            en[a[j]] = j;
            sum += dp[st[a[j]]][en[a[j]]];
        }
        for (int j = i; j < n; j++) {
            freq[a[j]] = 0;
            st[a[j]] = -1;
            en[a[j]] = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (st[a[i]] == -1) {
            st[a[i]] = i;
        }
        en[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        if (i == en[a[i]]) {
            ans += dp[st[a[i]]][en[a[i]]];
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
