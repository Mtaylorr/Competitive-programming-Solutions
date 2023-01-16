//https://codeforces.com/problemset/problem/515/E
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

struct node {
    // define the variables
    ll mx = -1e18;
    ll mn = 1e18;
    ll ans = 0;

    node() {
        // define initial values
    }
    void apply(ll ma, ll mi) {
        // define apply operation
        mx = ma;
        mn = mi;
    }
};

void unite(node &res, const node &a, const node &b) {
    // define the union operation
    ll ans = max(a.ans, b.ans);
    ans = max(ans, a.mx - b.mn);
    ans = max(ans, b.mx - a.mn);
    ll mx = max(a.mx, b.mx);
    ll mn = min(a.mn, b.mn);
    res.ans = ans;
    res.mx = mx;
    res.mn = mn;
}

int n, m;
int d[N], h[N];
ll s[N];
node spt[N][20];
int po[20];

ll query(int l, int r) {
    int len = r - l + 1;
    node res;
    for (int i = 19; i >= 0; i--) {
        if (po[i] <= len) {
            unite(res, res, spt[l][i]);
            l += po[i];
            len -= po[i];
        }
    }
    return res.ans;
}

void test_case() {
    for (int i = 0; i < 20; i++) {
        po[i] = 1 << i;
    }
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = n; i < 2 * n; i++) {
        h[i] = h[i % n];
        d[i] = d[i % n];
    }
    ll sm = 0;
    for (int i = 0; i < 2 * n; i++) {
        s[i] = sm;
        sm += d[i];
    }
    for (int i = 0; i < 2 * n; i++) {
        spt[i][0].apply(s[i] + 2 * h[i], s[i] - 2 * h[i]);
    }
    for (int j = 1; po[j] <= 2 * n; j++) {
        for (int i = 0; i + po[j] <= 2 * n; i++) {
            unite(spt[i][j], spt[i][j - 1], spt[i + po[j - 1]][j - 1]);
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int l, r;
        if (a > b) {
            l = b + 1;
            r = a - 1;
        } else {
            l = b + 1;
            r = a + n - 1;
        }

        ll rs = query(l, r);
        cout << rs << "\n";
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
