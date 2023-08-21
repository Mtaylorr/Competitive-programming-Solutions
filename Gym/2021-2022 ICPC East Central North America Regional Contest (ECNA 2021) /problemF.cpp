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
const long double eps = 1e-6;

struct Point {
    long double x, y;
    Point() {}
    Point(long double x, long double y) : x(x), y(y) {}
};

long double dist(Point x, Point y) {
    return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}

struct Circle {
    Point center;
    long double r;
    long double s;
    Circle(){};
    Circle(Point _center, long double r, long double s) : r(r), s(s) {
        center = _center;
    }
    long double area() { return r * r; }
};

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

vector<Circle> circles;
int n;

vector<int> cur[105];
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        long double x, y, r, s;
        cin >> x >> y >> r >> s;
        circles.emplace_back(Point(x, y), r, s);
    }
    while (circles.size() > 1) {
        dsu.init(n);
        vector<Circle> ncircles;
        vector<pair<long double, pair<int, int> > > tmp;
        for (int i = 0; i < circles.size(); i++) {
            for (int j = i + 1; j < circles.size(); j++) {
                long double d = dist(circles[i].center, circles[j].center) -
                                circles[i].r - circles[j].r;
                tmp.pb({(d) / (circles[i].s + circles[j].s), {i, j}});
            }
        }
        sort(all(tmp));
        set<int> st;
        int idx = 0;
        long double mn = max((long double)0, tmp[0].fi);
        /*for (auto &u : tmp) {
            cout << u.fi << " ";
        }
        cout << endl;
        */

        while (idx < tmp.size() && tmp[idx].fi <= mn + eps) {
            dsu.uni(tmp[idx].se.fi, tmp[idx].se.se);
            // dbg(tmp[idx].se.fi, tmp[idx].se.se);
            idx++;
        }
        // dbg(mn);
        for (int i = 0; i < circles.size(); i++) {
            circles[i].r += circles[i].s * mn;
        }
        for (int i = 0; i < n; i++) {
            cur[i].clear();
        }
        for (int i = 0; i < circles.size(); i++) {
            int idi = dsu.getid(i);
            cur[idi].pb(i);
        }
        for (int i = 0; i < circles.size(); i++) {
            if (dsu.id[i] != i) continue;
            if (cur[i].size() == 1) {
                ncircles.pb(circles[i]);
                continue;
            }
            if (cur[i].size() == 0) continue;
            long double smx = 0;
            long double smy = 0;
            long double smarea = 0;
            long double mxs = 0;
            for (auto &u : cur[i]) {
                smx += circles[u].center.x;
                smy += circles[u].center.y;
                smarea += circles[u].area();
                mxs = max(mxs, circles[u].s);
            }
            smx /= (sz(cur[i]));
            smy /= (sz(cur[i]));
            Point ncenter = Point(smx, smy);
            long double nr = sqrt(smarea);
            ncircles.pb(Circle(ncenter, nr, mxs));
        }
        circles = ncircles;
    }
    cout << fixed << setprecision(20) << circles[0].center.x << " "
         << circles[0].center.y << "\n";
    cout << circles[0].r << endl;
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
