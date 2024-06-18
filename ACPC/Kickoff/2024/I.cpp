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

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) { return (upper_bound(all(values), x) - values.begin()) - 1; }
    int greaterThanOrEqual(ll x) { return (lower_bound(all(values), x) - values.begin()); }
    ll decompress(int p) { return values[p]; }
} compressor;

int n;
ll s[N], e[N], c[N];
vector<int> add[N];
ll mx[N];
ll solve(ll C) {
    ll curmx = 0;
    ll ans = 0;
    for (int i = 0; i < compressor.n; i++) {
        for (auto &u : add[i]) {
            if (c[u] > C) continue;
            ans = max(ans, curmx + 1);
            mx[e[u]] = max(mx[e[u]], curmx + 1);
        }
        curmx = max(curmx, mx[i]);
        mx[i] = 0;
    }
    return ans;
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> e[i] >> c[i];
    }
    compressor.init();
    for (int i = 0; i < n; i++) {
        compressor.add(s[i]);
        compressor.add(e[i]);
    }
    compressor.run();
    for (int i = 0; i < n; i++) {
        s[i] = compressor.compress(s[i]);
        e[i] = compressor.compress(e[i]);
    }
    for (int i = 0; i < compressor.n + 1; i++) {
        add[i].clear();
    }
    for (int i = 0; i < n; i++) {
        add[s[i]].push_back(i);
    }
    ll mx = solve(1e18);
    ll l = 0;
    ll r = 1e18;
    while (l < r) {
        ll md = (l + r) / 2;
        if (solve(md) == mx) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    cout << mx << " " << l << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
