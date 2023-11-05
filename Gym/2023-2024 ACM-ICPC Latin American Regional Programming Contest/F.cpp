// Mtaylor
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
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
    int greatestSmallerThanOrEqual(ll x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    int greaterThanOrEqual(ll x) {
        return (lower_bound(all(values), x) - values.begin());
    }
    ll decompress(int p) { return values[p]; }
} compressor;

ll n;

void test_case() {
    cin >> n;
    int fmx = min(n, (ll)1000000);
    vector<ll> ans;
    vector<ll> tmp;
    for (int i = 2; i <= fmx; i++) {
        tmp.clear();
        ll x = n;
        while (x) {
            tmp.pb(x % i);
            x /= i;
        }
        bool cond = true;
        for (int j = 0; j < tmp.size() / 2; j++) {
            if (tmp[j] != tmp[tmp.size() - 1 - j]) {
                cond = false;
            }
        }
        if (cond) {
            ans.pb(i);
        }
    }
    for (ll j = 1; j * j <= n; j++) {
        if (n / j <= fmx) break;
        if (n % j == 0) {
            ll y = j;
            ll w = n / y;
            if (w - 1 >= 0 && y < w - 1 && w > fmx && w <= n) {
                ans.pb(w - 1);
            }
            y = n / j;
            w = n / y;
            if (w - 1 >= 0 && y < w - 1 && w > fmx && w <= n) {
                ans.pb(w - 1);
            }
        }
    }
    sort(all(ans));
    ans.resize(unique(all(ans)) - ans.begin());
    if (ans.size()) {
        for (auto &u : ans) {
            cout << u << " ";
        }
    } else {
        cout << "*";
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
