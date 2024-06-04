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

int dp[N];
int t[N][2];
int d[N];
int n, q;
int l;
bitset<300005> bs;
map<int, vector<int> > pos;

void test_case() {
    cin >> n >> q;
    int mx = 0;
    ll sumslow = 0;
    ll sumfast = 0;
    for (int i = 0; i <= 3e5; i++) {
        dp[i] = (1e9) + 5;
    }
    bs[0] = 1;
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> t[i][0] >> t[i][1];
        mx = max(mx, t[i][0]);
        pos[t[i][1]].pb(i);
        pos[t[i][0]].pb(-1);
        sumfast += d[i];
    }
    for (auto &u : pos) {
        // reach u.fi
        int ct = u.fi;
        for (auto &v : u.se) {
            if(v==-1)continue;
            bs |= bs << d[v];
            sumfast -= d[v];
            sumslow += d[v];
        }
        if (sumslow >= 6e5 || ct < mx) continue;
        int md = (sumslow + 1) / 2;
        while (md >= 0 && bs[md] == 0) {
            md--;
        }
        int rem = max((ll)md, sumslow - md);
        rem += sumfast;
        if (rem <= 3e5) {
            dp[rem] = min(dp[rem], ct);
        }
    }
    for(int i=1;i<=3e5;i++){
        dp[i]=min(dp[i],dp[i-1]);
    }
    while (q--) {
        cin >> l;
        if (dp[l] < 1e9) {
            cout << dp[l] << endl;
        } else {
            cout << -1 << endl;
        }
    }
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
