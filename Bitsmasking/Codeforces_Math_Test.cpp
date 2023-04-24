//https://codeforces.com/contest/1622/problem/E
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

int n, m;
int x[N];
ll val[N];
string s[11];
int perm[N];

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    ll ans = -1e18;
    int target_msk = 0;
    vector<int> tmp;
    for (int i = 0; i < m; i++) {
        tmp.pb(i);
    }
    for (int msk = 0; msk < (1 << n); msk++) {
        ll rs = 0;
        for (int j = 0; j < m; j++) {
            val[j] = 0;
        }
        for (int i = 0; i < n; i++) {
            if ((msk >> i) & 1) {
                rs += x[i];
                for (int j = 0; j < m; j++) {
                    if (s[i][j]=='1') {
                        val[j]--;
                    }
                }
            } else {
                rs -= x[i];
                for (int j = 0; j < m; j++) {
                    if (s[i][j]=='1') {
                        val[j]++;
                    }
                }
            }
        }
        sort(all(tmp), [](int &x, int &y) { return val[x] < val[y]; });

        for (int i = 1; i <= m; i++) {
            rs += (i * 1ll * val[tmp[i - 1]]);
        }

        if (ans < rs) {
            ans = rs;
            target_msk = msk;
        }
    }
    for (int j = 0; j < m; j++) {
        val[j] = 0;
    }
    for (int i = 0; i < n; i++) {
        if ((target_msk >> i) & 1) {
            for (int j = 0; j < m; j++) {
                if (s[i][j]=='1') {
                    val[j]--;
                }
            }
        } else {
            for (int j = 0; j < m; j++) {
                if (s[i][j]=='1') {
                    val[j]++;
                }
            }
        }
    }
    sort(all(tmp), [](int &x, int &y) { return val[x] < val[y]; });
    for (int i = 1; i <= m; i++) {
        perm[tmp[i - 1]] = i;
    }
    for (int i = 0; i < m; i++) {
        cout << perm[i] << " ";
    }
    cout << endl;
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
