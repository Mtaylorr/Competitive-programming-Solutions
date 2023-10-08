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

struct Point {
    double x, y;
};

struct line {
    Point p1, p2;
};

bool onLine(line l1, Point p) {
    // Check whether p is on the line or not
    if (p.x <= max(l1.p1.x, l1.p2.x) && p.x >= min(l1.p1.x, l1.p2.x) &&
        (p.y <= max(l1.p1.y, l1.p2.y) && p.y >= min(l1.p1.y, l1.p2.y)))
        return true;

    return false;
}

int direction(Point a, Point b, Point c) {
    double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

    if (val == 0)

        // Collinear
        return 0;

    else if (val < 0)

        // Anti-clockwise direction
        return 2;

    // Clockwise direction
    return 1;
}

bool isIntersect(line l1, line l2) {
    // Four direction for two lines and points of other line
    int dir1 = direction(l1.p1, l1.p2, l2.p1);
    int dir2 = direction(l1.p1, l1.p2, l2.p2);
    int dir3 = direction(l2.p1, l2.p2, l1.p1);
    int dir4 = direction(l2.p1, l2.p2, l1.p2);

    // When intersecting
    if (dir1 != dir2 && dir3 != dir4) return true;

    // When p2 of line2 are on the line1
    if (dir1 == 0 && onLine(l1, l2.p1)) return true;

    // When p1 of line2 are on the line1
    if (dir2 == 0 && onLine(l1, l2.p2)) return true;

    // When p2 of line1 are on the line2
    if (dir3 == 0 && onLine(l2, l1.p1)) return true;

    // When p1 of line1 are on the line2
    if (dir4 == 0 && onLine(l2, l1.p2)) return true;

    return false;
}
Point poly[N];
int n;
int x[N], y[N];
vector<int> adj[N];
bool ispointingdown[N];
bool checkInside(Point p) {
    // When polygon has less than 3 edge, it is not polygon
    if (n < 3) return false;

    // Create a point at infinity, y is same as point p
    line exline = {p, {1000000, p.y}};
    int count = 0;
    int i = 0;
    do {
        // Forming a line from two consecutive points of
        // poly
        line side = {poly[i], poly[(i + 1) % n]};
        if (isIntersect(side, exline)) {
            // If side is intersects exline
            if (direction(side.p1, p, side.p2) == 0) return onLine(side, p);
            count++;
        }
        i = (i + 1) % n;
    } while (i != 0);

    // When count is odd
    return count & 1;
}
struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;

void test_case() {
    cin >> n;
    dsu.init(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        poly[i] = {(double)x[i], (double)y[i]};
    }
    for (int i = 0; i < n; i++) {
        int l = i;
        int r = (l + 1) % n;
        if (y[r] == y[l]) {
            dsu.uni(l, r);
        }
    }
    for (int i = 0; i < n; i++) {
        int l = i;
        int r = (l + 1) % n;
        // dbg(l, r);
        if (y[r] > y[l]) {
            adj[dsu.getid(r)].pb(dsu.getid(l));
        } else if (y[l] > y[r]) {
            adj[dsu.getid(l)].pb(dsu.getid(r));
        }
    }
    for (int i = 0; i < n; i++) {
        int a = (i - 1 + n) % n;
        int b = i;
        int c = (i + 1) % n;
        int dxa = x[a] - x[b];
        int dxc = x[c] - x[b];
        int dya = y[a] - y[b];
        int dyc = y[c] - y[b];
        double dx = dxa + dxc;
        double dy = dya + dyc;
        double norm = sqrt(dx * dx + dy * dy);
        dx /= norm;
        dy /= norm;
        double nx = x[b] + dx * 0.2;
        double ny = y[b] + dy * 0.2;
        ispointingdown[dsu.getid(i)] = dy > 0 && checkInside({nx, ny});
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dsu.getid(i) == i && ispointingdown[dsu.getid(i)] &&
            adj[dsu.getid(i)].size() == 0) {
            ans++;
        }
    }
    cout << ans;
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
