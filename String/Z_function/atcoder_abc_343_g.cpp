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
string s[N];
bool done[N];
const int Z_N = 2 * N;
struct ZAlgo {
    int Z[Z_N];
    void run(string &s) {
        Z[0] = 0;
        int l = 1, r = 1;
        int n = s.size();
        for (int i = 1; i < n; i++) {
            int x = Z[i - l];
            if (i + x >= r) {
                l = i;
                r = max(r, i);
                while (r < n && s[r - l] == s[r]) r++;
                Z[i] = r - l;
            } else {
                Z[i] = Z[i - l];
            }
        }
    }
} z_algo;
int dp[20][1 << 20];
int mx[20][20];

int solve(int p, int msk) {
    if (msk == (1 << n) - 1) return 0;
    int &rs = dp[p][msk];
    if (rs != -1) return rs;
    rs = 1e9;
    for (int i = 0; i < n; i++) {
        if (msk & (1 << i)) continue;
        rs = min(rs, (int)s[i].size() - mx[p][i] + solve(i, msk + (1 << i)));
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    sort(s, s + n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (s[i] == s[j]) continue;
            string st = s[i] + "#" + s[j];
            z_algo.run(st);
            int idx = s[i].size() + 1;
            for (int k = 0; k < s[j].size(); k++) {
                int p = z_algo.Z[k + idx];
                if (p == s[i].size()) {
                    done[i] = 1;
                } else if (p == s[j].size() - k) {
                    mx[j][i] = max(mx[j][i], p);
                }
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (s[i - 1] == s[i]) {
            done[i - 1] = 1;
        }
    }
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (done[i]) {
            cur += (1 << i);
        }
    }
    if (cur == (1 << n) - 1) {
        int r = 0;
        for (int i = 0; i < n; i++) {
            r = max(r, (int)s[i].size());
        }
        cout << r << endl;
        return;
    }
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        if (!done[i]) {
            ans = min(ans, (int)s[i].size() + solve(i, cur + (1 << i)));
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
