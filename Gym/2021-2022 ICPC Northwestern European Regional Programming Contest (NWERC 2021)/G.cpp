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
const int N = 5e3 + 5;

string s[N];
int l[N];
int pos[N];
int dpw[N][N];
int dp[N];
int ans[N][N];
int w;
int n;
int cc = 0;
int cr;
int width[N];

int solve(int p) {
    if (p >= n) {
        return 0;
    }
    int &rs = dp[p];
    if (rs != -1) return rs;
    rs = 1e9;
    for (int j = p; j <= min(n - 1, p + cr - 1); j++) {
        rs = min(rs, dpw[p][j] + 1 + solve(j + 1));
    }
    return rs;
}

void findans(int p, int cc = 0) {
    if (p >= n) {
        return;
    }
    pos[p] = cc;
    for (int j = p; j <= min(n - 1, p + cr - 1); j++) {
        if (dpw[p][j] + 1 + solve(j + 1) == dp[p]) {
            width[cc] = dpw[p][j];
            findans(j + 1, cc + 1);
            return;
        }
    }
}

int ok(int r) {
    memset(dp, -1, sizeof(dp));
    cr = r;
    return solve(0);
}
int idx[N];
void test_case() {
    cin >> n >> w;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        l[i] = s[i].size();
    }
    for (int i = 0; i < n; i++) {
        int mx = 0;
        for (int j = i; j < n; j++) {
            mx = max(mx, l[j]);
            dpw[i][j] = mx;
        }
    }
    int l = 1;
    int r = n;
    while (l < r) {
        int md = (l + r) / 2;
        if (ok(md) <= w + 1) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    cr = l;
    int curw = ok(l);
    memset(pos, -1, sizeof(pos));
    findans(0);
    int cc = 0;
    for (int i = 0; i < n; i++) {
        cc = max(cc, pos[i]);
    }
    cc++;
    cout << l << " " << cc << endl;
    for (int i = 0; i < cc; i++) {
        cout << width[i] << " ";
    }
    memset(ans, -1, sizeof(ans));
    int cp = -1;
    for (int i = 0; i < n; i++) {
        if (pos[i] != -1) {
            cp = pos[i];
        }
        // dbg(i, cp);
        ans[idx[cp]++][cp] = i;
    }
    cout << endl;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < cc; j++) {
            if (ans[i][j] == -1) {
                string tmp = "";
                while (tmp.size() < width[j] + 1) {
                    tmp += " ";
                }
                cout << tmp;
            } else {
                int idx = ans[i][j];
                while (s[idx].size() < width[j] + 1) {
                    s[idx] += " ";
                }
                cout << s[idx];
            }
        }
        cout << endl;
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
