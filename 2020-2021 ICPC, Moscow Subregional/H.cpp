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

int a, b, x, y;
bool vis[6][6][6][6][2];
int ans[6][6][6][6];

void solve(int ca, int cb, int cx, int cy, int r) {
    int oa = a - x - ca;
    int ob = b - y - cb;
    int ox = x - cx;
    int oy = y - cy;
    // dbg(ca, cb, cx, cy, r);
    // dbg(oa, ob, ox, oy, r);
    if (ca + cx > cb + cy && (cb + cy)) return;
    if (oa + ox > ob + oy && (ob + oy)) return;

    if (vis[ca][cb][cx][cy][r]) return;
    vis[ca][cb][cx][cy][r] = 1;

    if (cx) {
        solve(oa, ob, ox + 1, oy, r ^ 1);
        if (ca) {
            solve(oa + 1, ob, ox + 1, oy, r ^ 1);
        }
        if (cb) {
            solve(oa, ob + 1, ox + 1, oy, r ^ 1);
        }
        if (cy) {
            solve(oa, ob, ox + 1, oy + 1, r ^ 1);
        }
        if (cx >= 2) {
            solve(oa, ob, ox + 2, oy, r ^ 1);
        }
    }
    if (cy) {
        solve(oa, ob, ox, oy + 1, r ^ 1);
        if (ca) {
            solve(oa + 1, ob, ox, oy + 1, r ^ 1);
        }
        if (cb) {
            solve(oa, ob + 1, ox, oy + 1, r ^ 1);
        }
        if (cy >= 2) {
            solve(oa, ob, ox, oy + 2, r ^ 1);
        }
    }
}

void preprocess() {
    for (a = 0; a <= 5; a++) {
        for (b = a; b <= 5; b++) {
            for (x = 0; x <= a; x++) {
                for (y = 0; y <= b; y++) {
                    memset(vis, 0, sizeof(vis));
                    solve(a - x, b - y, x, y, 0);
                    bool cond = vis[a - x][b - y][x][y][1];
                    if (cond) {
                        ans[a][b][x][y] = 1;
                    }
                }
            }
        }
    }
    // a = 3, b = 3, x = 3, y = 3;
    // solve(0, 0, 3, 3, 0);
}

void test_case() {
    cin >> a >> x >> b >> y;
    if (x == 0 && y == 0) {
        cout << "No\n";
        return;
    }
    if (a > b) {
        cout << "No\n";
        return;
    }
    if (a <= 5 && b <= 5) {
        if (ans[a][b][x][y]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
        return;
    }
    if (a == b) {
        cout << "No\n";
        return;
    }
    if (b == a + 1) {
        if (x >= 1 && y >= 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
        return;
    }
    cout << "Yes\n";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    preprocess();
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
