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

bitset<101> bs[105];
int a[N];
int p, q;
unordered_map<bitset<101>, ll> dp;
int n;
ll solve(bitset<101> rs) {
    int index = -1;
    if (dp.count(rs)) {
        return dp[rs];
    }
    for (int j = 0; j < n; j++) {
        if (rs[j] == 0) {
            index = j;
            break;
        }
    }
    if (index == -1) {
        return 0;
    }
    ll ans = 0;
    for (int j = 0; j < n; j++) {
        if (bs[j][index] && rs[j] == 0) {
            ans = max(ans, a[j] + solve(rs | bs[j]));
        }
    }
    return dp[rs] = ans;
}

void test_case() {
    cin >> p >> q;
    for (int i = p; i <= q; i++) {
        a[i - p] = i;
    }
    n = q - p + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (__gcd(a[i], a[j]) > 1) {
                bs[i][j] = 1;
            }
        }
        bs[i][i] = 1;
    }
    bitset<101> rs;
    cout << solve(rs) << endl;
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
