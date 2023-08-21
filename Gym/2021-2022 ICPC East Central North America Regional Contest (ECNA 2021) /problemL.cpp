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

int dx[] = {1, 1, -1, -1};
int dy[] = {1, -1, 1, -1};
int a[55][55];
int n, m;
vector<int> sorted;
void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] != -1) sorted.pb(a[i][j]);
        }
    }
    sort(all(sorted));
    vector<int> sti = {0, 0, n - 1, n - 1};
    vector<int> stj = {0, m - 1, 0, m - 1};
    int idx = 0;
    int ans = 1e9;
    for (int k = 0; k < 4; k++) {
        idx = 0;
        int rs = 0;
        for (int d = 0; d <= n + m - 2; d++) {
            multiset<int> tmp;
            for (int i = 0; i < n; i++) {
                int j = d - i;
                int x = sti[k] + dx[k] * i;
                int y = stj[k] + dy[k] * j;
                if (x >= 0 && x < n && y >= 0 && y < m) {
                    if (a[x][y] != -1) {
                        tmp.insert(a[x][y]);
                    }
                }
            }
            int sze = tmp.size();
            for (int j = 0; j < sze; j++) {
                if (tmp.count(sorted[j + idx])) {
                    tmp.erase(tmp.find(sorted[j + idx]));
                } else {
                    rs++;
                }
            }
            idx +=sze;
        }
        ans = min(ans, rs);
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
