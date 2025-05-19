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
int pos[N];
int pref[N][21];
int suff[N][21];
const int MOD = 1e9 + 7;
void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }

    for (int i = 0; i < 21; i++) {
        pref[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 21; j++) {
            pref[i][j] = pref[i - 1][j];
            if ((1 << j) & p[i]) {
                pref[i][j] = i;
            }
        }
    }
    for (int i = 0; i < 21; i++) {
        suff[n + 1][i] = n + 1;
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 21; j++) {
            suff[i][j] = suff[i + 1][j];
            if ((1 << j) & p[i]) {
                suff[i][j] = i;
            }
        }
    }
    int lf = pos[0];
    int rg = pos[0];
    int cmex = 1;
    int ans = 0;
    while (cmex != n + 1) {
        while (cmex < n && pos[cmex] >= lf && pos[cmex] <= rg) {
            cmex++;
        }
        for (int i = 0; i < 21; i++) {
            int lflb = 1;
            int lfub = min(pref[rg][i], lf);
            if (cmex < n && pos[cmex] < lf) {
                lflb = pos[cmex] + 1;
            }
            int rglb = max(rg, suff[lf][i]);
            int rgub = n;
            if (cmex < n && pos[cmex] > rg) {
                rgub = pos[cmex] - 1;
            }
            // dbg(i, lflb, lfub, rglb, rgub, lf, rg);
            if (lflb <= lfub) {
                int x = (lfub - lflb + 1) % MOD;
                x = (x * 1ll * (rgub - rg + 1)) % MOD;
                x = (x * 1ll * (1 << i)) % MOD;
                x = (x * 1ll * cmex) % MOD;
                ans = (ans + 0ll + x) % MOD;
            }
            if (rglb <= rgub) {
                int x = (rgub - rglb + 1) % MOD;
                x = (x * 1ll * (lf - lflb + 1)) % MOD;
                x = (x * 1ll * (1 << i)) % MOD;
                x = (x * 1ll * cmex) % MOD;
                ans = (ans + 0ll + x) % MOD;
            }
            if (lflb <= lfub && rglb <= rgub) {
                int x = (lfub - lflb + 1) % MOD;
                x = (x * 1ll * (rgub - rglb + 1)) % MOD;
                x = (x * 1ll * (1 << i)) % MOD;
                x = (x * 1ll * cmex) % MOD;
                ans = (ans + 0ll + MOD - x) % MOD;
            }
        }
        if (cmex == n) break;
        lf = min(lf, pos[cmex]);
        rg = max(rg, pos[cmex]);
    }
    cout << ans << endl;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif
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
