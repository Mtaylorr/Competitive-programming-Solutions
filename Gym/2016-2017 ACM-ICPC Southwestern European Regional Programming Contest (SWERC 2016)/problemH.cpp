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

ll CNK[33][33];
ll cnk(int n, int k) {
    if (k < 0) return 0;
    if (k > n) return 0;
    if (k == 0) return 1;
    if (CNK[n][k] != -1) return CNK[n][k];
    return CNK[n][k] = cnk(n - 1, k - 1) + cnk(n - 1, k);
}
set<ll> dp[35][35];
int cd;
ll cur = 1;
int d, h;

void test_case() {
    memset(CNK, -1, sizeof(CNK));
    cin >> d >> h;
    for (int i = 0; i <= h - 1; i++) {
        dp[0][i].insert(1);
    }
    for (int i = 1; i < d; i++) {
        for (int j = 0; j <= h - 1; j++) {
            for (int k = 0; k <= j; k++) {
                ll x = cnk(j, k);
                for (auto &u : dp[i - 1][j - k]) {
                    dp[i][j].insert(x * u);
                }
            }
        }
    }
    for (auto &u : dp[d - 1][h - 1]) {
        cout << u << endl;
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
