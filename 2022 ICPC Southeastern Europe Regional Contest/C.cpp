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

int n, m;
int a[16][1005];
vector<int> v[1005];
bitset<1005> bs[16];
int pre[1005][1005];
vector<int> val[1005];

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            x--;
            bs[i][x] = 1;
        }
    }
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    for (int mask = 0; mask < (1 << m); mask++) {
        bitset<1005> b;
        int nb = 0;
        for (int i = 0; i < m; i++) {
            if ((1 << i) & (mask)) {
                nb++;
                b = b | bs[i];
            }
        }
        int sz = 0;
        for (int i = 0; i < n; i++) {
            sz += b[i];
        }
        int e = n - 1 - sz;
        int v = 1;
        if (nb % 2 == 0) {
            v = -1;
        }

        for (int i = 0; i < n; i++) {
            if (!b[i]) {
                pre[i][e] += v;
            }
        }
    }
    vector<int> ord;
    for (int i = 0; i < n; i++) {
        val[i].assign(n + 1, 0);
        ord.pb(i);
        for (int j = 0; j < n; j++) {
            int x = pre[i][j];
            // dbg(i, j, pre[i][j]);
            pre[i][j + 1] += (x / 2);
            x = x % 2;
            pre[i][j] = x;
            if (x == -1) {
                pre[i][j] = 1;
                pre[i][j + 1]--;
            }

            val[i][j] = pre[i][j];
        }
        val[i][n] = pre[i][n];
        reverse(all(val[i]));
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j <= n; j++) {
    //         cout << val[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    sort(all(ord), [](int &x, int &y) {
        if (val[x] != val[y]) return val[x] > val[y];
        return x < y;
    });

    for (int i = 0; i < n; i++) {
        cout << ord[i] + 1 << " ";
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
