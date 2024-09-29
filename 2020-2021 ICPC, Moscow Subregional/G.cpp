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

ll a[1005][1005];
ll pref[1005][1005];
ll b[N];
int n, m, k;
void test_case() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            pref[i][j] = a[i][j];
            if (j) {
                pref[i][j] += pref[i][j - 1];
            }
        }
    }
    ll c = 0;
    for (int j = 0; j < n; j++) {
        vector<ll> v;
        for (int i = 0; i < k; i++) {
            v.push_back(pref[i][j] - c);
        }
        sort(all(v));
        ll median = v[v.size() / 2];
        c += median;
        b[j] = median;
    }
    for(int i=0;i<n;i++){
        cout <<  b[i]  <<  " ";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
