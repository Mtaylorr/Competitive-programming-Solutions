//https://codeforces.com/contest/551/problem/E
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
const int N = 5e5 + 5;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int n, q;
unordered_map<int, int, custom_hash> p[N][2];
ll sum[N];
ll a[N];

struct SQRTDecomposition {
    int sq;
    int n;
    void init(int _n) {
        n = _n;
        sq = sqrt(n);
    }
    void build(int l, int r) {
        int bl = l / sq;
        int br = r / sq;
        for (int i = bl; i <= br; i++) {
            // clear data
            p[i][0].clear();
            p[i][1].clear();
        }
        for (int i = l; i <= r; i++) {
            int bi = i / sq;
            // update the value
            if (a[i] > 1e9) continue;
            p[bi][1][a[i]] = i;
            if (p[bi][0].count(a[i]) == 0) {
                p[bi][0][a[i]] = i;
            }
        }
    }

    inline int bstart(int bi) { return bi * sq; }
    inline int bend(int bi) { return min(n - 1, (bi + 1) * sq - 1); }

    void unlazy(int bi) {
        // bi : block index
        // apply stored changes to the block
        int l = bstart(bi);
        int r = bend(bi);
        if (!sum[bi]) return;
        p[bi][0].clear();
        p[bi][1].clear();
        for (int i = l; i <= r; i++) {
            a[i] += sum[bi];
        }
        sum[bi] = 0;
    }

    void updateIterative(int l, int r, int v) {
        // update the parameters here and apply change for each position
        int bi = l / sq;
        unlazy(bi);  // apply stored changes
        for (int i = l; i <= r; i++) {
            a[i] += v;
        }
        l = bstart(bi);
        r = bend(bi);
        build(l, r);
    }
    void updateBlock(int bi, int v) {
        // update the parameters here and store the changes for the block
        sum[bi] += v;
    }

    template <typename... M>
    void updateRange(int l, int r, const M &...v) {
        int bl = l / sq;
        int br = r / sq;
        if (bl == br) {
            updateIterative(l, r, v...);
        } else {
            updateIterative(l, (bl + 1) * sq - 1, v...);
            for (int i = bl + 1; i < br; i++) {
                updateBlock(i, v...);
            }
            updateIterative(br * sq, r, v...);
        }
    }

    // !!!  ATTENTION to the return type and type of ans in query function  !!!

    void queryIterative(int l, int r, int v, pair<int, int> &ans) {
        // query the full range l to r
        int bi = l / sq;
        for (int i = l; i <= r; i++) {
            if (a[i] + sum[bi] == v) {
                ans.fi = min(ans.fi, i);
                ans.se = max(ans.se, i);
            }
        }
    }
    void queryBlock(int bi, int v, pair<int, int> &ans) {
        // query the block bi
        if (v - sum[bi] >= 1 && p[bi][0].count(v - sum[bi])) {
            ans.fi = min(ans.fi, p[bi][0][v - sum[bi]]);
            ans.se = max(ans.se, p[bi][1][v - sum[bi]]);
        }
    }

    pair<int, int> mrg(pair<int, int> l, pair<int, int> r) {
        // apply merge operation here
        return {min(l.fi, r.fi), max(l.se, r.se)};
    }

    void query(int l, int r, int v, pair<int, int> &ans) {
        int bl = l / sq;
        int br = r / sq;
        if (bl == br) {
            queryIterative(l, r, v, ans);
        } else {
            queryIterative(l, (bl + 1) * sq - 1, v, ans);
            for (int i = bl + 1; i < br; i++) {
                queryBlock(i, v, ans);
            }
            queryIterative(br * sq, r, v, ans);
        }
    }
} sq;
int t, l, r, x;
void test_case() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sq.init(n);
    sq.build(0, n - 1);
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r >> x;
            --l, --r;
            sq.updateRange(l, r, x);
        } else {
            cin >> x;
            pair<int, int> ans = {1e9, -1};
            sq.query(0, n - 1, x, ans);
            if (ans.se != -1) {
                cout << ans.se - ans.fi << endl;
            } else {
                cout << -1 << endl;
            }
        }
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
