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

int p[N], l[N];
int n, k, m;
int lst[N];
int sum[N];
int pos[N];
void test_case() {
    cin >> n >> m >> k;
    memset(lst, -1, sizeof(lst));
    for (int i = 1; i <= k; i++) {
        cin >> p[i] >> l[i];
        if (lst[l[i]] == -1) {
            lst[l[i]] = p[i];
            sum[l[i]] += 100;
        } else if (lst[l[i]] == p[i]) {
            lst[l[i]] = -1;
            continue;
        } else {
            sum[l[i]] -= 100;
            sum[l[i]] += abs(p[i] - lst[l[i]]);
            lst[l[i]] = -1;
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << sum[i] << " ";
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
