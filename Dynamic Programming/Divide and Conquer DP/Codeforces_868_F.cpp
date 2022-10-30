//https://codeforces.com/problemset/problem/868/F
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
int a[N];
ll dp[2][N];
int freq[N];

int lf = 1;
int rg = 0;
ll sm = 0;

void add(int i) {
    sm += freq[a[i]];
    freq[a[i]]++;
}
void rem(int i) {
    freq[a[i]]--;
    sm -= freq[a[i]];
}

void travel(int tl, int tr) {
    while (lf > tl) {
        add(--lf);
    }
    while (rg < tr) {
        add(++rg);
    }
    while (lf < tl) {
        rem(lf++);
    }
    while (rg > tr) {
        rem(rg--);
    }
}
void init() {
    memset(freq, 0, sizeof(freq));
    lf = 1;
    rg = 0;
    sm = 0;
    travel(1, n);
}

void calc(int id, int l, int r, int ql, int qr) {
    if (l > r) return;
    int md = (l + r) / 2;
    pair<ll, int> p = {(ll)1e18, -1};
    travel(ql, md);
    ll csm = sm;
    for (int i = ql; i <= min(qr, md); i++) {
        p = min(p, make_pair(csm + dp[id ^ 1][i - 1], i));
        freq[a[i]]--;
        csm -= freq[a[i]];
    }
    for (int i = ql; i <= min(qr, md); i++) {
        freq[a[i]]++;
    }
    dp[id][md] = p.fi;
    int opt = p.se;
    calc(id, l, md - 1, ql, opt);
    calc(id, md + 1, r, opt, qr);
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        dp[0][i] = 1e18;
    }
    for (int i = 1; i <= k; i++) {
        init();
        calc(i & 1, 1, n, 1, n);
    }
    cout << dp[k & 1][n];
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
