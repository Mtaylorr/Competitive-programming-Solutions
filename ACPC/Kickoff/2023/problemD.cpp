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
    int greatestSmallerThanOrEqual(ll x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    int greaterThanOrEqual(ll x) {
        return (lower_bound(all(values), x) - values.begin());
    }
    ll decompress(int p) { return values[p]; }
} compressor;

vector<int> v[2][N];
int x[N], y[N];
int n, q;
int xs, ys;
void getLower(int &a, int &b, int t) {
    int p = lower_bound(all(v[t][b]), a) - v[t][b].begin();
    p--;
    if (p < 0) {
        return;
    }
    a = v[t][b][p];
}
void getUpper(int &a, int &b, int t) {
    int p = upper_bound(all(v[t][b]), a) - v[t][b].begin();
    if (p == v[t][b].size()) {
        return;
    }
    a = v[t][b][p];
}

void test_case() {
    cin >> n;
    compressor.init();
    cin >> xs >> ys;
    compressor.add(xs);
    compressor.add(ys);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        compressor.add(x[i]);
        compressor.add(y[i]);
    }
    compressor.run();
    for (int i = 0; i < n; i++) {
        x[i] = compressor.compress(x[i]);
        y[i] = compressor.compress(y[i]);
        v[1][x[i]].pb(y[i]);
        v[0][y[i]].pb(x[i]);
    }
    for (int i = 0; i < compressor.n; i++) {
        sort(all(v[0][i]));
        sort(all(v[1][i]));
    }
    xs = compressor.compress(xs);
    ys = compressor.compress(ys);
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        switch (c) {
            case 'L': {
                getLower(xs, ys, 0);
                break;
            }
            case 'R': {
                getUpper(xs, ys, 0);
                break;
            }
            case 'D': {
                getLower(ys, xs, 1);
                break;
            }
            case 'U': {
                getUpper(ys, xs, 1);
                break;
            }
        }
        cout << compressor.decompress(xs) << " " << compressor.decompress(ys)
             << endl;
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
