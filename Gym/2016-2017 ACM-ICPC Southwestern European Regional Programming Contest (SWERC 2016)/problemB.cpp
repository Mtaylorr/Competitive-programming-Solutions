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

int n, x[N], y[N];
vector<pair<int, int> > v[2];

bool cmp(pair<int, int> &x, pair<int, int> &y) {
    return x.fi * 1ll * y.se < y.fi * 1ll * x.se;
}

bool cmpeq(pair<int, int> &x, pair<int, int> &y) {
    return x.fi * 1ll * y.se <= y.fi * 1ll * x.se;
}

int getlower(int a, int b) {
    pair<int, int> p = {a, b};
    int rs = 0;
    if (v[0].size() && cmp(v[0][0], p)) {
        int l = 0;
        int r = v[0].size() - 1;
        while (l < r) {
            int md = (l + r + 1) / 2;
            if (cmp(v[0][md], p)) {
                l = md;
            } else {
                r = md - 1;
            }
        }
        rs += (l + 1);
    }
    if (v[1].size() && cmp(p, v[1].back())) {
        int l = 0;
        int r = v[1].size() - 1;
        while (l < r) {
            int md = (l + r) / 2;
            if (cmp(p, v[1][md])) {
                r = md;
            } else {
                l = md + 1;
            }
        }
        rs += v[1].size() - l;
    }

    return rs;
}

int getlowerEqual(int a, int b) {
    pair<int, int> p = {a, b};
    int rs = 0;
    if (v[0].size() && cmpeq(v[0][0], p)) {
        int l = 0;
        int r = v[0].size() - 1;
        while (l < r) {
            int md = (l + r + 1) / 2;
            if (cmpeq(v[0][md], p)) {
                l = md;
            } else {
                r = md - 1;
            }
        }
        rs += (l + 1);
    }
    if (v[1].size() && cmpeq(p, v[1].back())) {
        int l = 0;
        int r = v[1].size() - 1;
        while (l < r) {
            int md = (l + r) / 2;
            if (cmpeq(p, v[1][md])) {
                r = md;
            } else {
                l = md + 1;
            }
        }
        rs += v[1].size() - l;
    }

    return rs;
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    int mx = 0;
    int mn = n;
    int nb = 0;
    int nb2 = 0;
    for (int i = 1; i < n; i++) {
        if (x[i] <= x[0]) {
            nb++;
        }
        if (x[i] < x[0]) nb2++;
    }
    mx = max(mx, nb + 1);
    mn = min(mn, nb2 + 1);
    nb = 0;
    nb2 = 0;
    for (int i = 1; i < n; i++) {
        if (y[i] <= y[0]) {
            nb++;
        }
        if (y[i] < y[0]) nb2++;
    }
    mx = max(mx, nb + 1);
    mn = min(mn, nb2 + 1);
    int eq = 0;
    int bef = 0;
    int aft = 0;
    for (int i = 1; i < n; i++) {
        int dx = x[0] - x[i];
        int dy = y[0] - y[i];
        if (dx == 0 && dy == 0) {
            eq++;
        } else if (dx == 0) {
            if (dy >= 0) {
                bef++;
            } else {
                aft++;
            }
        } else if (dy == 0) {
            if (dx >= 0) {
                bef++;
            } else {
                aft++;
            }
        } else {
            if (dx * dy < 0) {
                if (dy < 0) {
                    v[0].pb({abs(dy), abs(dx)});
                } else {
                    v[1].pb({abs(dy), abs(dx)});
                }
            } else if (dx < 0) {
                aft++;
            } else {
                bef++;
            }
        }
    }
    sort(all(v[0]), cmp);
    sort(all(v[1]), cmp);
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            if (i == 0 && j == 0) continue;
            int lo = getlower(i, j) + 1;
            int loe = getlowerEqual(i, j) + 1;
            int rmin = lo + bef;
            int rmax = loe + bef + eq;
            mx = max(mx, rmax);
            mn = min(mn, rmin);
        }
    }
    cout << n - mx + 1 << " " << n - mn + 1 << endl;
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
