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
const int MOD = 1e9 + 7;

/*
9
10
4 4 6 5 4 3 6 6 4 6
10
5 5 3 6 4 3 6 3 5 5
10
3 5 6 5 6 6 6 4 5 4
10
6 3 6 6 4 4 4 4 4 3
10
3 5 5 6 6 6 6 3 3 4
10
4 5 5 4 6 4 5 3 4 3
10
5 5 3 4 5 3 6 4 6 6
10
3 5 3 4 5 6 5 4 4 3
10
3 5 4 6 3 4 6 6 3 5
*/


int n;
int a[N];
ll freq[N];
ll dpl[N];
ll dpr[N];
ll dps[N];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dpl[i] = 0;
        dps[a[i]] = 0;
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                dpl[i] += freq[j];
                if (j * j != a[i]) {
                    dpl[i] += freq[a[i] / j];
                }
            }
        }
        freq[a[i]]++;
    }
    for (int i = 0; i < n; i++) {
        freq[a[i]]--;
    }
    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        dpr[i] = 0;
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                dpr[i] += freq[j];
                if (j * j != a[i]) {
                    dpr[i] += freq[a[i] / j];
                }
            }
        }
        freq[a[i]]++;
        ans = (ans + (dpl[i] * 1ll * dps[a[i]]) % MOD) % MOD;
        dps[a[i]] = (dps[a[i]] + dpr[i]) % MOD;
    }

    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        freq[a[i]]--;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
