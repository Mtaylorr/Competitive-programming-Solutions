//https://codeforces.com/problemset/problem/2/C
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

typedef complex<double> point;
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a, b) ((b) - (a))
#define polar(r, t) ((r) * exp(point(0, (t))))
#define angle(v) (atan2((v).Y, (v).X))
#define length(v) ((double)hypot((v).Y, (v).X))
#define lengthSqr(v) (dot(v, v))
#define dot(a, b) ((conj(a) * (b)).real())
#define cross(a, b) ((conj(a) * (b)).imag())
#define rotate(v, t) (polar(v, t))
#define rotateabout(v, t, a) (rotate(vec(a, v), t) + (a))
#define reflect(p, m) ((conj((p) / (m))) * (m))
#define normalize(p) ((p) / length(p))
#define same(a, b) (lengthSqr(vec(a, b)) < EPS)
#define mid(a, b) (((a) + (b)) / point(2, 0))
#define perp(a) (point(-(a).Y, (a).X))
#define colliner pointOnLine
const double PI = 4 * atan(1);

enum STATE { IN, OUT, BOUNDRY };

// get angle opposite to side a
double cosRule(double a, double b, double c) {
    // Handle denom = 0
    double res = (b * b + c * c - a * a) / (2 * b * c);
    if (fabs(res - 1) < EPS) res = 1;
    if (fabs(res + 1) < EPS) res = -1;
    return acos(res);
}

int circleCircleIntersection(const point& c1, const double& r1, const point& c2, const double& r2, point& res1, point& res2) {
    if (same(c1, c2) && fabs(r1 - r2) < EPS) {
        res1 = res2 = c1;
        return fabs(r1) < EPS ? 1 : OO;
    }
    double len = length(vec(c1, c2));
    if (fabs(len - (r1 + r2)) < EPS || fabs(fabs(r1 - r2) - len) < EPS) {
        point d, c;
        double r;
        if (r1 > r2)
            d = vec(c1, c2), c = c1, r = r1;
        else
            d = vec(c2, c1), c = c2, r = r2;
        res1 = res2 = normalize(d) * r + c;
        return 1;
    }
    if (len > r1 + r2 || len < fabs(r1 - r2)) return 0;
    double a = cosRule(r2, r1, len);
    point c1c2 = normalize(vec(c1, c2)) * r1;
    res1 = rotate(c1c2, a) + c1;
    res2 = rotate(c1c2, -a) + c1;
    return 2;
}

int circleLineIntersection(const point& p0, const point& p1, const point& cen, double rad, point& r1, point& r2) {
    // handle degenerate case if p0 == p1
    double a, b, c, t1, t2;
    a = dot(p1 - p0, p1 - p0);
    b = 2 * dot(p1 - p0, p0 - cen);
    c = dot(p0 - cen, p0 - cen) - rad * rad;
    double det = b * b - 4 * a * c;
    int res;
    if (fabs(det) < EPS)
        det = 0, res = 1;
    else if (det < 0) {
        res = 0;
        det = 0;
    } else
        res = 2;
    det = sqrt(det);
    t1 = (-b + det) / (2 * a);
    t2 = (-b - det) / (2 * a);
    r1 = p0 + t1 * (p1 - p0);
    r2 = p0 + t2 * (p1 - p0);
    return res;
}

bool intersect(const point& a, const point& b, const point& p, const point& q, point& ret) {
    // handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)

    double d1 = cross(p - a, b - a);
    double d2 = cross(q - a, b - a);
    if (abs(d1 - d2) < EPS) {
        return 1e9;
    }
    ret = (d1 * q - d2 * p) / (d1 - d2);
    if (fabs(d1 - d2) > EPS) return 1;
    return 0;
}

double x[3], y[3], r[3];

vector<vector<double> > eqs;

void addEq(int i, int j) {
    double ax = r[j] * r[j] - r[i] * r[i];
    double bx = 2 * x[j] * r[i] * r[i] - 2 * x[i] * r[j] * r[j];
    double cx = r[j] * r[j] * x[i] * x[i] - r[i] * r[i] * x[j] * x[j];
    double ay = ax;
    double by = 2 * y[j] * r[i] * r[i] - 2 * y[i] * r[j] * r[j];
    double cy = r[j] * r[j] * y[i] * y[i] - r[i] * r[i] * y[j] * y[j];
    if (ax == 0) {
        // it's a line find 2 points on the line
        if (by != 0) {
            eqs.push_back({0, 0, -((cy + cx) / by), 1, -((cy + cx + bx) / by)});
        } else if (bx != 0) {
            eqs.push_back({0, -((cy + cx) / bx), 0, -((cy + cx + by) / bx), 1});
        }
    } else {
        bx /= ax;
        cx /= ax;
        ay /= ax;
        by /= ax;
        cy /= ax;
        ax = 1.0;
        double center_x = -bx / 2;
        double center_y = -by / 2;
        double r = -cx - cy + center_x * center_x + center_y * center_y;
        if (r >= 0) {
            eqs.push_back({1, center_x, center_y, sqrt(r)});
        }
    }
}

double getAngle(point p, int i) {
    point pi = {x[i], y[i]};
    double d = length(p - pi);
    return atan2(r[i] / 2, d);
}

void test_case() {
    for (int i = 0; i < 3; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            addEq(i, j);
        }
    }
    sort(all(eqs));
    vector<point> points;
    for (int i = 0; i < eqs.size(); i++) {
        for (int j = i + 1; j < eqs.size(); j++) {
            if (eqs[i][0] == 1) {
                point p1, p2;
                int rs = circleCircleIntersection({eqs[i][1], eqs[i][2]}, eqs[i][3], {eqs[j][1], eqs[j][2]}, eqs[j][3], p1, p2);
                if (rs < 1e9 && rs) {
                    points.push_back(p1);
                    points.push_back(p2);
                }
            } else if (eqs[j][0] == 0) {
                point p1;
                int r = intersect({eqs[i][1], eqs[i][2]}, {eqs[i][3], eqs[i][4]}, {eqs[j][1], eqs[j][2]}, {eqs[j][3], eqs[j][4]}, p1);
                if (r && r < 1e9) {
                    points.push_back(p1);
                }
            } else {
                point p1, p2;
                int rs = circleLineIntersection({eqs[i][1], eqs[i][2]}, {eqs[i][3], eqs[i][4]}, {eqs[j][1], eqs[j][2]}, eqs[j][3], p1, p2);
                if (rs) {
                    points.push_back(p1);
                    points.push_back(p2);
                }
            }
        }
    }
    double bstAngle = 0;
    bool found = false;
    point rs;
    for (auto& p : points) {
        vector<double> angles;
        for (int i = 0; i < 3; i++) {
            angles.pb(getAngle(p, i));
        }
        sort(all(angles));
        if (abs(angles[0] - angles.back()) > EPS) {
            continue;
        }
        found = true;
        if (angles[0] > bstAngle) {
            rs = p;
            bstAngle = angles[0];
        }
    }
    if (found) {
        cout << fixed << setprecision(20) << rs.X << " " << rs.Y << endl;
    }
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
