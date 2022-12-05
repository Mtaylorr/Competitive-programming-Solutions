//https://codeforces.com/problemset/problem/1168/C

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

int n, q;
int a[N];
int reach[N][20];
int pos[20][20];
int x, y;
void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            pos[i][j] = 1e9;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int msk = 0;
        for (int j = 0; j < 20; j++) {
            reach[i][j] = 1e9;
        }
        for (int j = 0; j < 20; j++) {
            if ((1 << j) & a[i]) {
                reach[i][j] = i;
                for (int k = 0; k < 20; k++) {
                    reach[i][k] = min(reach[i][k], pos[j][k]);
                }
            }
        }
        for (int j = 0; j < 20; j++) {
            if ((1 << j) & a[i])
                for (int k = 0; k < 20; k++) {
                    pos[j][k] = min(pos[j][k], reach[i][k]);
                }
        }
    }
    while (q--) {
        cin >> x >> y;
        x--, y--;
        bool cond = false;
        for (int i = 0; i < 20; i++) {
            if ((a[y] & (1 << i)) && reach[x][i] <= y) {
                cond = true;
                break;
            }
        }
        if (cond) {
            cout << "Shi\n";
        } else {
            cout << "Fou\n";
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    T = 1;
    // cin >>T;
    while (T--) {
        solve();
    }
    return 0;
}

