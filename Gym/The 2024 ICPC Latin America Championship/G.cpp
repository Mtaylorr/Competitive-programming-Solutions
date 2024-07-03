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

double dp[N];
double sum[N];
double sumdiv[N];
double summul[N];
int n;
double w[N];
vector<int> divs[N];
void test_case() {
    cin >> n;
    double sumw = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        sumw += w[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            divs[j].pb(i);
            sumdiv[j] = sumdiv[j] + w[i];
            // if (j != i) summul[i] = summul[i] + (w[j] / sumw);
        }
    }
    double ans = 0;
    sum[1] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = sum[i];
        double s = 0;
        for (int j = 2 * i; j <= n; j += i) {
            double s2 = 0;

            for (auto &u : divs[i]) {
                if (__gcd(j / i, i / u) != 1) continue;
                if (u * 1ll * (j / i) > n) continue;
                int x = u * (j / i);
                s2 += w[x] / (sumw - sumdiv[i]);
            }
            sum[j] += s2 * dp[i];
        }
        ans += dp[i] * ((i != 1) + (sumdiv[i] / (sumw - sumdiv[i])));
    }
    cout << fixed << setprecision(10) << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
