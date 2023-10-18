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

ll x[N];
ll val[N];
ll sum[N];
int n;
ll r[N];
ll ans[N];

void solve(ll u) {
    map<ll, int> freq;
    for (int i = 0; i < n; i++) {
        freq[r[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            ll v = sum[i] - u;
            ans[i] = v;
            if (freq[v] == 0) {
                return;
            }
            freq[v]--;
        } else {
            ll v = sum[i] + u;
            ans[i] = v;
            if (freq[v] == 0) continue;
            freq[v]--;
        }
    }
    for(int i=0;i<n;i++){
        cout << ans[i] << " ";
    }
    exit(0);
}

void test_case() {
    cin >> n;
    ll s = 0;
    ll mx = -1e18;
    ll mn = 1e18;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        if (i > 0) {
            s = -s + x[i] - x[i - 1];
        }
        sum[i] = s;
        val[i] = s;
        if (i % 2 == 0) {
            val[i] *= -1;
        }
        if (i % 2)
            mx = max(mx, val[i]);
        else {
            mn = min(mn, val[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    if (n == 1) {
        cout << r[0];
        return;
    }
    sort(r, r + n);
    solve(mx - r[n - 1]);
    solve(r[n - 1] + mn);
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
