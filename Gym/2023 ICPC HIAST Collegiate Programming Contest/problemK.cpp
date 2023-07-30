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
const int N = 5e5 + 5;

int n, m;
string s[N];
int q;
int l[N][26], r[N][26];
void test_case() {
    memset(l, -1, sizeof(l));
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < m; j++) {
            int x = s[i][j] - 'a';
            if (l[i][x] == -1) {
                l[i][x] = j;
            }
            r[i][x] = j;
        }
    }
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            if ((l[a][i] == -1) || (l[b][i] == -1)) continue;
            int lf = max(l[a][i], l[b][i]);
            int rg = min(r[a][i], r[b][i]);
            if (lf <= rg) {
                ans += rg - lf + 1;
            }
        }
        cout << ans << endl;
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
