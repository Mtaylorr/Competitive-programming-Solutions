https://codeforces.com/contest/1767/problem/E

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
int m;
int c[N];
int x[N];
int con[50][50];
bool vis[(1 << 20) + 5];
int sz[N];
ll po[50];
int notmask[N];
int dp[(1 << 20) + 5][2];
vector<int> cols;
bool valid(int& msk) {
    for (int i = 0; i < cols.size(); i++) {
        if (((po[i] & msk) == 0) &&
            (msk & notmask[cols[i]]) != notmask[cols[i]]) {
            return 0;
        }
    }
    return 1;
}

int curmax;

void calc(int msk, int id) {
    if (vis[msk]) {
        return;
    }
    vis[msk] = 1;
    int rs = 0;
    for (int i = 0; i < cols.size(); i++) {
        if ((msk & po[i]) ) {
            rs += x[cols[i]];
        }
    }

    if (valid(msk)) {
        dp[msk][id] = rs;
    }
    for (int i = 0; i < cols.size(); i++) {
        if ((msk & po[i]) == 0) {
            calc(msk + po[i], id);
        }
    }
}

void solve() {
    po[0] = 1;
    for (int i = 1; i <= 40; i++) {
        po[i] = 2 * po[i - 1];
    }
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        c[i]--;
        sz[c[i]]++;
    }
    for (int i = 0; i < m; i++) {
        cin >> x[i];
    }
    if (m == 1) {
        cout << x[0] << endl;
        return;
    }
    con[c[0]][c[0]] = 1;
    con[c[n - 1]][c[n - 1]] = 1;
    for (int i = 0; i < n - 1; i++) {
        con[c[i]][c[i + 1]] = 1;
        con[c[i + 1]][c[i]] = 1;
    }
    int lsz = m / 2;
    ;
    for (int i = 0; i < lsz; i++) {
        cols.pb(i);
    }
    for (int i = 0; i < cols.size(); i++) {
        for (int j = 0; j < cols.size(); j++) {
            if (con[cols[i]][cols[j]]) {
                notmask[cols[i]] += po[j];
            }
        }
    }
    for (int i = 0; i < po[cols.size()]; i++) {
        dp[i][0] = 1e9;
    }
    calc(0, 0);
    for (int msk = po[cols.size()] - 1; msk >= 0; msk--) {
        for (int j = 0; j < cols.size(); j++) {
            if ((po[j] & msk) == 0) {
                dp[msk][0] = min(dp[msk][0], dp[msk + po[j]][0]);
            }
        }
    }
    cols.clear();
    for (int i = lsz; i < m; i++) {
        cols.pb(i);
    }
    for (int i = 0; i < cols.size(); i++) {
        notmask[cols[i]] = 0;
        for (int j = 0; j < cols.size(); j++) {
            if (con[cols[i]][cols[j]]) {
                notmask[cols[i]] += po[j];
            }
        }
    }
    for (int i = 0; i < po[cols.size()]; i++) {
        dp[i][1] = 1e9;
        vis[i]=0;
    }

    calc(0, 1);
    int ans = 2e9;
    for (int i = 0; i < cols.size(); i++) {
        notmask[cols[i]] = 0;
        for (int j = 0; j < lsz; j++) {
            if (con[cols[i]][j]) {
                notmask[cols[i]] += po[j];
            }
        }
    }
    for (int msk = 0; msk < po[cols.size()]; msk++) {
        int othmsk = 0;
        for (int j = 0; j < cols.size(); j++) {
            if ((msk & po[j]) == 0) {
                othmsk = othmsk | notmask[cols[j]];
            }
        }
        ans = min(ans, dp[msk][1] + dp[othmsk][0]);
    }
    cout << ans;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
