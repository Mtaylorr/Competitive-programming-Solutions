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

int n;
int dp[N];

int solve(int p) {
    if (p == 0) return 0;
    if (p == 1) return 1;
    int &rs = dp[p];
    if (rs != -1) return rs;
    rs = 1e9;
    string s = to_string(p);
    if (s.size() >= 2)
        for (int i = 1; i <= s.size() - 1; i++) {
            string lf = s.substr(0, i);
            string rg = s.substr(i);
            if (rg[0] == '0') continue;
            rs = min(rs, solve(stoi(lf)) + solve(stoi(rg)));
        }
    for (int i = 1; i <= min(p-1,(p+1)/2); i++) {
        rs = min(rs, solve(i) + solve(p - i));
    }
    for (int i = 2; i * i <= p; i++) {
        if (p % i == 0) {
            rs = min(rs, solve(i) + solve(p / i));
        }
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n;
    cout << solve(n) << endl;
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
