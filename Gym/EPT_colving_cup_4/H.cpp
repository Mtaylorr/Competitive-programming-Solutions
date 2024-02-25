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
const int N = 1e6 + 5;

int n, p[N];
int q[N];
int pos[N];

int solve(int ans) {
    if (ans <= 0) return 0;
    return 1 + solve(ans / 2);
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    int nb = 0;
    int mx = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (pos[i + 1] < pos[i]) {
            nb++;
        }
    }
    int ans = solve(nb);
    for (int i = 0; i < n; i++) {
        q[p[i] - 1] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        pos[q[i]] = i;
    }
    nb = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (pos[i + 1] < pos[i]) {
            nb++;
        }
    }
    ans += solve(nb);
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
