//https://codeforces.com/problemset/problem/999/F
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

int nb[N];
int freq[N];
int n, k;
int h[N];
int c;
vector<vector<int> > dp;

int calc(int r, int p) {
    if (r == 0) {
        return 0;
    }
    if (p == 0) {
        return 0;
    }
    if (dp[r][p] != -1) return dp[r][p];
    int rs=0;
    for(int i=0;i<=min(k,r);i++){
        rs=max(rs, h[i]+calc(r-i, p-1));
    }
    return dp[r][p]=rs;
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n * k; i++) {
        cin >> c;
        freq[c]++;
    }
    for (int i = 0; i < n; i++) {
        cin >> c;
        nb[c]++;
    }
    for(int i=1;i<=k;i++){
        cin >> h[i];
    }
    int ans = 0;
    for (int i = 1; i <= 1e5; i++) {
        if (freq[i] == 0 || nb[i]==0) continue;
        dp.resize(freq[i]+1);
        for (int j = 0; j <= freq[i]; j++) {
            dp[j].assign(nb[i]+1, -1);
        }
       
        ans += calc(freq[i], nb[i]);
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
