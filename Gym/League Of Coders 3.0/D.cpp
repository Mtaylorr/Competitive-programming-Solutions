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

int n, a[1 << 18];
vector<int> ord;
vector<int> adj[1 << 18];
vector<int> r;
int dp[20][1 << 18], tmp[20][1 << 18];
void test_case() {
    cin >> n;
    int l = n;
    n = (1 << n);
    for (int i = 0; i < n; i++) {
        ord.pb(i);
        cin >> a[i];
        int p = i;
        int id = 0;
        for (int j = 0; j < l; j++) {
            dp[id][p] = max(dp[id][p], a[i]);
            tmp[id][p] = dp[id][p];
            id++;
            p /= 2;
        }
    }
    sort(all(ord), [](int &x, int &y) { return a[x] > a[y]; });
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        if (p != 0) {
            adj[p - 1].pb(i);
        }
    }
    int ans = 0;
    for (auto &i : ord) {
        int x = a[i];
        int nb = adj[i].size();
        vector<int> &r = adj[i];
        vector<int> o;
        sort(all(r));
        bool cond = true;
        for (auto &p : r) {
            int y = p;
            int id = 0;
            int c = 0;
            for (int j = 0; j < l; j++) {
                if (tmp[id][y] > x) break;
                if (tmp[id][y] == x) {
                    cond = false;
                    break;
                }
                tmp[id][y] = x;
                y /= 2;
                id++;
            }
        }
        if (cond) {
            for (auto &p : r) {
                int y = p;
                isnt id = 0;
                int c = 0;
                for (int j = 0; j < l; j++) {
                    if (tmp[id][y] > x) break;
                    dp[id][y] = tmp[id][y];
                    y /= 2;
                    id++;
                }
            }
            ans += r.size();
        } else {
            for (auto &p : r) {
                int y = p;
                int id = 0;
                int c = 0;
                for (int j = 0; j < l; j++) {
                    if (tmp[id][y] > x) break;
                    tmp[id][y] = dp[id][y];
                    y /= 2;
                    id++;
                }
            }
        }
    }
    cout << ans << endl;
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
