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

map<string, int> ids;
int x[N], y[N];
int n, m;
vector<pair<int, int>> combined;
void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ids[s] = i;
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        string lf = "";
        string rg = "";
        for (auto &c : s) {
            if (c == '_') {
                swap(lf, rg);
            } else {
                lf += c;
            }
        }
        combined.push_back({ids[lf], ids[rg]});
    }
    ll ans = 1e18;
    for (int msk = 0; msk < (1 << n); msk++) {
        ll price = 0;
        for (int i = 0; i < n; i++) {
            if (msk & (1 << i)) {
                price += y[i];
            }
        }
        int done = 0;
        for (int i = 0; i < m; i++) {
            if (msk & (1 << combined[i].fi)) continue;
            if (msk & (1 << combined[i].se)) continue;
            if ((done & (1 << combined[i].fi)) == 0) {
                price += x[combined[i].fi];
                done += (1 << combined[i].fi);
            }
            if ((done & (1 << combined[i].se)) == 0) {
                price += x[combined[i].se];
                done += (1 << combined[i].se);
            }
        }
        ans=min(ans, price);
    }
    cout << ans << endl;
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
