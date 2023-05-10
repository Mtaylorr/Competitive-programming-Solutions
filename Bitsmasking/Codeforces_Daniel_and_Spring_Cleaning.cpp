//https://codeforces.com/problemset/problem/1245/F
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
int l, r;
ll dp[32][2][2][2][2];

ll solve(int p, int ael, int aer, int bel, int ber) {
    if (p < 0) {
        return 1;
    }
    ll &rs = dp[p][ael][aer][bel][ber];
    if (rs != -1) return rs;
    rs = 0;
    int cl = (l >> p) & 1;
    int cr = (r >> p) & 1;
    int al = ael ? cl : 0;
    int ar = aer ? cr : 1;
    int bl = bel ? cl : 0;
    int br = ber ? cr : 1;
    for (int i = al; i <= ar; i++) {
        for (int j = bl; j <= br; j++) {
            if (i == j && i) continue;
            rs += solve(p - 1, ael && (i == cl), aer && (i == cr),
                        bel && (j == cl), ber && (j == cr));
        }
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> l >> r;
    cout << solve(30, 1, 1, 1, 1) << endl;
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
