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

int n, a[N], b[N];
ll dp[N][4];
bool vis[N][4];
ll xa, xb;
ll solve(int p, int msk) {
    if (p >= n) {
        if (msk != 3) return -1e18;
        return 0;
    }
    ll &rs = dp[p][msk];
    if (vis[p][msk]) {
        return rs;
    }
    vis[p][msk] = 1;
    int ja = p;
    int jb = p;
    if (msk & 1) {
        ja--;
    }
    if (msk & 2) {
        jb--;
    }
    rs = -1e18;
    if (ja < n - 1 && jb < n - 1) {
        rs = abs(a[ja] - b[jb]) + solve(p + 1, msk);
    }

    if (msk == 0) {
        rs = max(rs, abs(xa - xb) + solve(p + 1, 3));
    }
    if ((msk & 1) == 0 && jb < n - 1) {
        rs = max(rs, abs(xa - b[jb]) + solve(p + 1, msk + 1));
    }
    if ((msk & 2) == 0 && ja < n - 1) {
        rs = max(rs, abs(a[ja] - xb) + solve(p + 1, msk + 2));
    }
    return rs;
}

vector<int> aa, bb;

void showAns(int p, int msk) {
    if (p >= n) {
        return;
    }
    ll rs = dp[p][msk];
    int ja = p;
    int jb = p;
    if (msk & 1) {
        ja--;
    }
    if (msk & 2) {
        jb--;
    }
    if (ja < n - 1 && jb < n - 1 && rs == abs(a[ja] - b[jb]) + solve(p + 1, msk)) {
        aa.push_back(a[ja]);
        bb.push_back(b[jb]);
        showAns(p + 1, msk);
        return;
    }
    if (msk == 0) {
        if (rs == abs(xa - xb) + solve(p + 1, 3)) {
            aa.push_back(xa);
            bb.push_back(xb);
            showAns(p + 1, 3);
            return;
        }
    }
    if ((msk & 1) == 0 && jb < n - 1) {
        if (rs == abs(xa - b[jb]) + solve(p + 1, msk + 1)) {
            aa.push_back(xa);
            bb.push_back(b[jb]);
            showAns(p + 1, msk + 1);
            return;
        }
    }
    aa.push_back(a[ja]);
    bb.push_back(xb);
    showAns(p + 1, msk + 2);
    return;
}

void test_case() {
    cin >> n;

    xa = n *1ll* (n + 1) / 2;
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
        xa -= a[i];
    }
    xb = n *1ll* (n + 1) / 2;
    for (int i = 0; i < n - 1; i++) {
        cin >> b[i];
        xb -= b[i];
    }
    ll ans = solve(0, 0);
    cout << ans << endl;
    showAns(0, 0);
    for (auto &u : aa) {
        cout << u << " ";
    }
    cout << endl;
    for (auto &u : bb) {
        cout << u << " ";
    }
    cout << endl;
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
