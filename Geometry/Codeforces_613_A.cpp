//https://codeforces.com/problemset/problem/613/A
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353 ;
const double eps = 1e-7;

typedef complex<double> point;
#define EPS 1e-9
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define length(v) ((double)hypot((v).Y,(v).X))
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())


double pointLineDist(const point& a, const point& b, const point& p)
{
    // handle degenrate case: (a,b) is point

    return fabs(cross(vec(a,b),vec(a,p)) / length(vec(a,b)));
}

double pointSegmentDist(const point& a, const point& b, const point& p)
{
    if (dot(vec(a,b),vec(a,p)) < EPS)
        return length(vec(a,p));
    if (dot(vec(b,a),vec(b,p)) < EPS)
        return length(vec(b,p));
    return pointLineDist(a, b, p);
}

int n;
double xp,yp;
double x[N],y[N];
set<int> s;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> xp >> yp;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }
    double mn = 1e18;
    for(int i=0;i<n;i++){
        point a = {x[i],y[i]};
        point b = {x[(i+1)%n],y[(i+1)%n]};
        point p = {xp,yp};
        double d = pointSegmentDist(a,b,p);
        mn=min(mn, d);
    }
    mn*=mn;
    double mx = 0;
    for(int i=0;i<n;i++){
        mx=max(mx, (x[i]-xp)*(x[i]-xp)+ (y[i]-yp)*(y[i]-yp));
    }
    double ans = 4*atan(1) * (mx-mn) ;
    cout << fixed << setprecision(10) << ans;

    return 0;
}
