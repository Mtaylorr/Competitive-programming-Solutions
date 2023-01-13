//https://codeforces.com/problemset/problem/940/F
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
    ll decompress(int p) { return values[p]; }
} compressor;

int n, q, m;
int a[N];
int timer;
int s, e;
int ti[N], l[N], r[N], ans[N], qi[N];
int p[N], bef[N], aft[N];
int freq[N];
int cnt[N];

void add(int x) {
    cnt[freq[x]]--;
    freq[x]++;
    cnt[freq[x]]++;
}

void rem(int x) {
    cnt[freq[x]]--;
    freq[x]--;
    cnt[freq[x]]++;
}

void upd(int id) {
    while (timer > ti[id]) {
        if (p[timer] >= s && p[timer] <= e) {
            rem(aft[timer]);
            add(bef[timer]);
        }
        a[p[timer]] = bef[timer];
        timer--;
    }
    while (timer < ti[id]) {
        timer++;
        if (p[timer] >= s && p[timer] <= e) {
            rem(bef[timer]);
            add(aft[timer]);
        }
        a[p[timer]] = aft[timer];
    }

    while (e < r[id]) add(a[++e]);

    while (s > l[id]) add(a[--s]);

    while (e > r[id]) rem(a[e--]);

    while (s < l[id]) rem(a[s++]);
}

void mo() {
    int B = pow(n, 2.0 / 3);
    sort(qi, qi + m, [B](int &a, int &b) {
        return mp(mp(l[a] / B, r[a] / B), ti[a]) <
               mp(mp(l[b] / B, r[b] / B), ti[b]);
    });
    s = 0;
    e = -1;
    for (int i = 0; i < m; i++) {
        int id = qi[i];
        upd(id);
        while (cnt[ans[id]]) {
            ans[id]++;
        }
    }
}

void test_case() {
    cnt[0] = 1e9;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compressor.add(a[i]);
    }
    for (int i = 0; i < q; i++) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            ti[m] = timer;
            qi[m] = m;
            cin >> l[m] >> r[m];
            --l[m], --r[m];
            m++;
        } else {
            timer++;
            cin >> p[timer];
            --p[timer];
            bef[timer] = a[p[timer]];
            cin >> aft[timer];
            a[p[timer]] = aft[timer];
            compressor.add(aft[timer]);
        }
    }
    compressor.run();

    for (int i = 0; i < n; i++) {
        a[i] = compressor.compress(a[i]);
    }
    for (int i = 1; i <= timer; i++) {
        bef[i] = compressor.compress(bef[i]);
        aft[i] = compressor.compress(aft[i]);
    }
    mo();
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
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
        test_case();
    }
    return 0;
}

