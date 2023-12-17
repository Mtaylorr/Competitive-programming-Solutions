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
string s;
int f[2];
int c[2];
void test_case() {
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; i++) {
        f[0] += s[i] == 'O';
        f[1] += s[i] == 'L';
    }
    for (int i = 0; i < n - 1; i++) {
        c[0] += s[i] == 'O';
        c[1] += s[i] == 'L';
        if (c[0] != f[0] - c[0] && c[1] != f[1] - c[1]) {
            cout << i + 1 << endl;
            return;
        }
    }
    cout << -1;
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
