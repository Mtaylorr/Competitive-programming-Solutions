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
int p, u;
int val[N][2];
vector<int> v[2][2];
void test_case() {
    int n;
    for (int k = 0; k < 2; k++) {
        cin >> p >> u;
        n = p + u;
        for (int i = 0; i < p; i++) {
            int x;
            cin >> x;
            v[k][0].pb(x);
            val[x][k] = 0;
        }
        for (int i = 0; i < u; i++) {
            int x;
            cin >> x;
            v[k][1].pb(x);
            val[x][k] = 1;
        }
        reverse(all(v[k][1]));
    }
    int ans = 0;

    for (int i = 0; i < 2; i++) {
        vector<int> tmp[2];
        for (auto &x : v[0][i]) {
            if (val[x][0] != val[x][1]) {
                ans++;
            } else {
                tmp[0].pb(x);
            }
        }
        for (auto &x : v[1][i]) {
            tmp[1].pb(x);
        }
        int nb = 0;
        int idx = 0;
        for (int j = 0; j < tmp[0].size(); j++) {
            if (idx >= tmp[1].size()) {
                ans += 2;
            } else if (tmp[0][j] == tmp[1][idx]) {
                idx++;
                continue;
            } else {
                ans += 2;
            }
        }
        /*for (auto &x : tmp[0]) {
            cout << x << " ";
        }
        cout << endl;
        for (auto &x : tmp[1]) {
            cout << x << " ";
        }
        cout << endl;*/
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
