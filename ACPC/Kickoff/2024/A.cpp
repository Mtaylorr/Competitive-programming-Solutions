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

int n, a[N];
int pos[20];

int pref[N], suff[N];
int mx[N];

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx[i] = -1;
    }
    pref[0] = (1 << 20) - 1;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] & a[i];
    }
    suff[n + 1] = (1 << 20) - 1;
    for (int i = n; i >= 1; i--) {
        suff[i] = suff[i + 1] & a[i];
    }
    memset(pos, -1, sizeof(pos));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 20; j++) {
            if (((1 << j) & a[i]) == 0) {
                pos[j] = i;
            }
        }
        vector<int> tmp;
        for (int j = 0; j < 20; j++) {
            if (pos[j] != -1) tmp.pb(pos[j]);
        }
        sort(rall(tmp));
        int cur = (1 << 20) - 1;
        for (auto &u : tmp) {
            cur = cur & a[u];
            int bef = pref[u - 1];
            int aft = suff[i + 1];
            int outside = bef & aft;
            if (outside == (1 << 20) - 1) {
                outside = 0;
            }
            if (cur == outside) {
                mx[i] = max(mx[i], u);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        mx[i] = max(mx[i], mx[i - 1]);
    }
    int q;
    cin >> q;
    int l, r;
    while (q--) {
        cin >> l >> r;
        if (mx[r] >= l) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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
