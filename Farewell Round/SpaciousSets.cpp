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

int n, k;
int a[N], b[N];
map<int, int> pos;
int dp[N][2];

int getright(int p) {
    int target = b[p] + k;
    return lower_bound(b, b + n, target) - b;
}

int getleft(int p) {
    int target = b[p] - k;
    return (upper_bound(b, b + n, target) - b) - 1;
}

int solveleft(int p) {
    if (p < 0) return 0;
    int &rs = dp[p][0];
    if (rs != -1) return rs;
    return rs = 1 + solveleft(getleft(p));
}
int solveright(int p) {
    if (p >= n) return 0;
    int &rs = dp[p][1];
    if (rs != -1) return rs;
    return rs = 1 + solveright(getright(p));
}

void test_case() {
    pos.clear();
    cin >> n >> k;
    for (int i = 0; i <= n; i++) {
        memset(dp[i], -1, sizeof(dp[i]));
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b, b + n);
    for (int i = 0; i < n; i++) {
        pos[b[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        int ans = 1;
        int nxrgt = getright(pos[a[i]]);
        ans += solveright(nxrgt);
        int nxtleft = getleft(pos[a[i]]);
        ans += solveleft(nxtleft);
        //dbg(pos[a[i]], nxtleft, nxrgt);
        cout << ans << " ";
    }
    cout << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
