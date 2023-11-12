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
const int N = 4e5 + 5;

int n, m, r;
int x[N], y[N];
int dx[N], dy[N];
unordered_map<int, int> st[N];
bool done[5005][4][1005];

int mxx[] = {1, 0, -1, 0};
int myy[] = {1, 0, -1, 0};
int mxy[] = {0, 1, 0, -1};
int myx[] = {0, -1, 0, 1};

bool vis[N];
void test_case() {
    cin >> n >> m >> r;
    int th = 200000;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        st[x[i] + th][y[i]] = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> dx[i] >> dy[i];
    }
    int ans = 0;
    int ansx = 0;
    int ansy = 0;
    multiset<pair<int, int> > anspos;
    vector<int> ord;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int o = 0; o < 4; o++) {
                if (done[i][o][j]) continue;
                bool cond = true;
                int sx = x[i] - mxx[o] * dx[j] - mxy[o] * dy[j];
                int sy = y[i] - myx[o] * dx[j] - myy[o] * dy[j];
                if (st[sx + th].count(sy)) {
                    continue;
                }
                ord.clear();
                for (int k = 0; k < m; k++) {
                    int ax = sx + mxx[o] * dx[k] + mxy[o] * dy[k];
                    int ay = sy + myx[o] * dx[k] + myy[o] * dy[k];
                    if (st[ax + th].count(ay) == 0) {
                        cond = false;
                        break;
                    }
                    int p = st[ax + th][ay];
                    ord.pb(p);
                    vis[p] = 1;
                    if (done[p][o][k]) {
                        cond = false;
                        break;
                    }
                }

                if (cond) {
                    for (int i = 0; i < n; i++) {
                        if (abs(sx - x[i]) + abs(sy - y[i]) <= r && !vis[i]) {
                            cond = false;
                            break;
                        }
                    }
                }
                for (int k = 0; k < ord.size(); k++) {
                    done[ord[k]][o][k] = 1;
                    vis[ord[k]] = 0;
                }

                if (cond) {
                    anspos.insert({sx, sy});
                    ansx = sx;
                    ansy = sy;
                }
            }
        }
        if (anspos.size() >= 2) break;
    }
    if (anspos.size() == 1) {
        cout << ansx << " " << ansy << endl;
    } else if (anspos.size() == 0) {
        cout << "Impossible\n";
    } else {
        cout << "Ambiguous\n";
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
