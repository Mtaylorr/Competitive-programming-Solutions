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

int n;
ll s;
ll a[1005][1005];
ll sum[2][1005];

bool valid(int x1, int y1, int x2, int y2) {
    int d = a[x1][y1] - a[x2][y2];
    if (x1 == x2 && y1 == y2) {
        return 0;
    }
    if (x1 == x2) {
        return sum[1][y1] - d == s && sum[1][y2] + d == s;
    } else if (y1 == y2) {
        return sum[0][x1] - d == s && sum[0][x2] + d == s;
    } else {
        return sum[1][y1] - d == s && sum[1][y2] + d == s && sum[0][x1] - d == s && sum[0][x2] + d == s;
    }
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            s += a[i][j];
        }
    }
    s /= n;
    set<int> rows, cols;
    for (int i = 0; i < n; i++) {
        ll x = 0;
        for (int j = 0; j < n; j++) {
            x += a[i][j];
        }
        sum[0][i] = x;
        if (x != s) {
            rows.insert(i);
        }
    }
    for (int i = 0; i < n; i++) {
        ll x = 0;
        for (int j = 0; j < n; j++) {
            x += a[j][i];
        }
        sum[1][i] = x;
        if (x != s) {
            cols.insert(i);
        }
    }
    if (rows.size() && cols.size()) {
        int px0 = *rows.begin();
        rows.erase(rows.begin());
        int px1 = *rows.begin();
        int py0 = *cols.begin();
        cols.erase(cols.begin());
        int py1 = *cols.begin();
        ll x = sum[0][px0];
        ll y = sum[0][px1];
        ll z = sum[1][py0];
        ll w = sum[1][py1];
        int d = a[px0][py0] - a[px1][py1];
        if (x - d == s && y + d == s && z - d == s && w + d == s) {
            cout << px0 + 1 << " " << py0 + 1 << endl;
            cout << px1 + 1 << " " << py1 + 1 << endl;
            return;
        }
        d = a[px0][py1] - a[px1][py0];
        if (x - d == s && y + d == s && z + d == s && w - d == s) {
            cout << px0 + 1 << " " << py1 + 1 << endl;
            cout << px1 + 1 << " " << py0 + 1 << endl;
            return;
        }

    } else if (rows.size()) {
        int p0 = *rows.begin();
        rows.erase(rows.begin());
        int p1 = *rows.begin();
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ll x = sum[0][p0];
                ll y = sum[0][p1];
                if (x - a[p0][j] + a[p1][k] == s && y - a[p1][k] + a[p0][j] == s) {
                    if (valid(p0, j, p1, k)) {
                        cout << p0 + 1 << " " << j + 1 << endl;
                        cout << p1 + 1 << " " << k + 1 << endl;
                        return;
                    }
                }
            }
        }
    } else {
        int p0 = *cols.begin();
        cols.erase(cols.begin());
        int p1 = *cols.begin();
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ll x = sum[1][p0];
                ll y = sum[1][p1];
                if (x - a[j][p0] + a[k][p1] == s && y - a[k][p1] + a[j][p0] == s) {
                    if (valid(j, p0, k, p1)) {
                        cout << j + 1 << " " << p0 + 1 << endl;
                        cout << k + 1 << " " << p1 + 1 << endl;
                        return;
                    }
                }
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
