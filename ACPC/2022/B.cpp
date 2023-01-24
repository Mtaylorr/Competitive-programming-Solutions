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

typedef complex<ll> point;
#define dot(a, b) ((conj(a) * (b)).real())
#define cross(a, b) ((conj(a) * (b)).imag())
#define vec(a, b) ((b) - (a))

bool aligned(point &x, point &y, point &z) {
    return cross(vec(x, y), vec(x, z)) == 0;
}

point pts[N];
set<pair<ll, ll> > vecs[N];
int n;
int x, y;
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        vecs[i].clear();
        cin >> x >> y;
        pts[i] = {x, y};
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            point ij = vec(pts[i], pts[j]);
            vecs[i].insert({ij.real(), ij.imag()});
        }
    }
    ll ans = 0;
    for (int b = 0; b < n; b++) {
        for (int c = 0; c < n; c++) {
            if (b == c) continue;
            ll e_lower = 0;
            ll e_upper = 0;
            for (int e = 0; e < n; e++) {
                if (e == b || e == c) continue;
                if (aligned(pts[b], pts[c], pts[e])) continue;
                point bc = vec(pts[b], pts[c]);
                point cb = vec(pts[c], pts[b]);
                point be = vec(pts[b], pts[e]);
                point ce = vec(pts[c], pts[e]);
                ll cbe = dot(bc, be);
                ll bce = dot(cb, ce);
                if (cbe > 0 && bce > 0) {
                    ll cr = cross(bc, be);

                    if (cr > 0) {
                        e_lower++;
                    } else {
                        e_upper++;
                    }
                }
            }
            ll a_lower = 0;
            ll a_upper = 0;
            for (int a = 0; a < n; a++) {
                if (a == b || a == c) continue;
                point bc = vec(pts[b], pts[c]);
                point ba = vec(pts[b], pts[a]);

                if (dot(bc, ba) == 0) {
                    if (vecs[c].count({ba.real(), ba.imag()})) {
                        ll cr = cross(bc, ba);
                        if (cr > 0) {
                            a_lower++;
                        } else {
                            a_upper++;
                        }
                    }
                }
            }
            ans += a_lower * e_upper;
            ans += a_upper * e_lower;
        }
    }
    cout << ans/2 << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
