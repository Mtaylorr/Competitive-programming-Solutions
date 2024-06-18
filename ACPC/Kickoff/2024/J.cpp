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

int vis[1005][1005];
pair<int, int> par[1005][1005];
int nxt[1005][1005];

int n;
void bfs(int x, int y) {
    memset(vis, 0, sizeof(vis));
    queue<pair<int, int> > q;
    par[x][y] = {-1, -1};
    q.push({x, y});
    pair<int, int> p;
    int st = 0;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        x = p.fi;
        y = p.se;
        for (int i = !st; i < 10; i++) {
            // dbg(i, x, y);
            int nx = (p.fi * 10 + i) % n;
            int ny = (p.se + i) % n;
            if (nx == 0 && ny == 0) {
                par[nx][ny] = {x, y};
                nxt[nx][ny] = i;
                return;
            }

            if (vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            par[nx][ny] = {x, y};
            nxt[nx][ny] = i;
            q.push({nx, ny});
        }
        st++;
    }
}

void test_case() {
    cin >> n;
    if (n < 10) {
        cout << n << endl;
        return;
    }
    bfs(0, 0);
    int x = par[0][0].fi;
    int y = par[0][0].se;
    string ans = "";
    ans += char('0' + nxt[0][0]);
    while (x != 0 || y != 0) {
        ans = ans + char('0' + nxt[x][y]);
        int nx = par[x][y].fi;
        int ny = par[x][y].se;
        x = nx;
        y = ny;
    }
    reverse(all(ans));
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
