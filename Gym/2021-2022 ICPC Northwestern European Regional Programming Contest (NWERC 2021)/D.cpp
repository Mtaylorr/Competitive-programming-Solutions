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
const int N = 2e6 + 10;
int n;
int x[N], y[N];
int mnsuff[N];
int mxsuff[N];
int mn[N], mx[N];

set<pair<int, int> > st[2][2];
int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
int dy[] = {0, 0, 1, -1, 1, 1, -1, -1};

bool ok(int b, int x, int y) {
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (st[0][b].count({nx, ny}) || st[1][b].count({nx, ny})) {
            return 0;
        }
    }
    return 1;
}
void test_case() {
    int th = (1e6) + 1;
    for (int i = 0; i < N; i++) {
        mn[i] = mnsuff[i] = 1e9;
        mx[i] = mxsuff[i] = 0;
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x[i] += th;
        y[i] += th;
        mn[x[i]] = min(mn[x[i]], y[i]);
        mx[x[i]] = max(mx[x[i]], y[i]);
    }
    for (int i = N - 2; i >= 0; i--) {
        mnsuff[i] = min(mn[i], mnsuff[i + 1]);
        mxsuff[i] = max(mxsuff[i + 1], mx[i]);
    }
    int l = 0;
    for (int i = 0; i < N; i++) {
        if (mx[i] != 0) {
            l = i;
            break;
        }
    }
    int r = 0;
    for (int i = 0; i < N; i++) {
        if (mx[i] != 0) {
            r = i;
        }
    }
    int tot = 1e9;

    int stu = mx[l];
    int std = mn[l];
    for (int _i = 0; _i < 2; _i++) {
        for (int _j = 0; _j < 2; _j++) {
            if (_i == _j && _i) continue;
            int yu = stu + _i;
            int yd = std - _j;
            int ans = 0;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    st[i][j].clear();
                }
            }
            ans += yu - yd + 1;
            for (int i = l; i <= r; i++) {
                // dbg("start");
                int id = (i & 1);
                st[id][0].clear();
                st[id][1].clear();
                if (mxsuff[i] == 0) {
                    break;
                }
                // dbg(i - th, yu - th, yd - th, ans);
                bool can_reduce_d = false;
                bool can_reduce_u = false;
                if (mx[i] >= yu) {
                    while (mx[i] > yu) {
                        yu++;
                        ans++;
                        st[id][0].insert({i - 1, yu});
                    }

                    ans++;
                    yu++;
                } else {
                    if (mxsuff[i] >= yu) {
                        yu++;
                    } else if (mxsuff[i] < yu - 1) {
                        can_reduce_u = true;
                    }
                    ans++;
                }
                if (mn[i] <= yd) {
                    while (mn[i] < yd) {
                        st[id][1].insert({i - 1, yd});
                        yd--;
                        ans++;
                    }
                    ans++;
                    yd--;
                } else {
                    if (mnsuff[i] > yd + 1) {
                        can_reduce_d = true;
                    } else if (mnsuff[i] <= yd) {
                        yd--;
                    }
                    ans++;
                }
                st[id][1].insert({i, yd});
                st[id][0].insert({i, yu});
                if (can_reduce_d && can_reduce_u) {
                    if (ok(0, i, yd + 1)) {
                        st[id][1].erase({i, yd});
                        yd++;
                        st[id][1].insert({i, yd});
                    }
                    if (ok(1, i, yu - 1)) {
                        st[id][0].erase({i, yu});
                        yu--;
                        st[id][0].insert({i, yu});
                    }
                } else if (can_reduce_d) {
                    if (ok(0, i, yd + 1)) {
                        st[id][1].erase({i, yd});
                        yd++;
                        st[id][1].insert({i, yd});
                    }
                } else if (can_reduce_u) {
                    if (ok(1, i, yu - 1)) {
                        st[id][0].erase({i, yu});
                        yu--;
                        st[id][0].insert({i, yu});
                    }
                }
                // dbg(i - th, yu - th, yd - th, ans);
            }
            // dbg(yu - th, yd - th);
            ans += yu - yd - 1;
            tot = min(tot, ans);
        }
    }
    cout << tot << endl;
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
