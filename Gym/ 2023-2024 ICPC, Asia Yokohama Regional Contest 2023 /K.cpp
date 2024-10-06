// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
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

const double eps = 1e-9;

long double query(int a, int b, int c, int d) {
    cout << "query " << a << " " << b << " " << c << " " << d << " " << endl;
    long double ans;
    cin >> ans;
    return ans;
}

bool isNotZero(double &ans) { return ans > eps; }

int getLeftx(int p) {
    int l = 0;
    int r = p;
    while (l < r) {
        int md = (l + r) / 2;
        double rs = query(md, 0, md, 1e5);
        if (isNotZero(rs)) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    return l - 1;
}

int getRightX(int p) {
    int l = p;
    int r = 1e5;
    while (l < r) {
        int md = (l + r + 1) / 2;
        double rs = query(md, 0, md, 1e5);
        if (isNotZero(rs)) {
            l = md;
        } else {
            r = md - 1;
        }
    }
    return l + 1;
}

void solveX(int &x, int &r) {
    int ind;
    for (int i = 0; i <= 1e5; i += 199) {
        double r = query(i, 0, i, 1e5);
        ind = i;
        if (isNotZero(r)) break;
    }
    int lx = getLeftx(ind);
    int rx = getRightX(ind);
    x = (lx + rx) / 2;
    r = (rx - lx) / 2;
}

void solveY(int x, int &y, int ra) {
    int l = 0;
    int r = 1e5;
    while (l < r) {
        int md = (l + r + 1) / 2;
        double rs = query(x, 0, x, md);
        if (isNotZero(rs)) {
            r = md - 1;
        } else {
            l = md;
        }
    }
    y = l + ra;
}

void test_case() {
    int x, r;
    int y;
    solveX(x, r);
    solveY(x, y, r);
    cout << "answer " << x << " " << y << " " << r << endl;
}

int main() {
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
