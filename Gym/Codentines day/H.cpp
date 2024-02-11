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

const int B[] = {151, 157};
const int MOD = 1e9 + 7;

int po[2][N];
string s[N];
pair<int, int> h[N];
int n;
pair<int, int> getHash(string &s) {
    int h0 = 0;
    int h1 = 0;
    for (int i = 0; i < s.size(); i++) {
        h0 = (h0 + 0ll + (((s[i] - 'A') + 1) * 1ll * po[0][i]) % MOD) % MOD;
        h1 = (h1 + 0ll + (((s[i] - 'A') + 1) * 1ll * po[1][i]) % MOD) % MOD;
    }
    return {h0, h1};
}
map<pair<int, int>, vector<int> > f;
map<pair<int, int>, vector<pair<int, int> > > f2;

void test_case() {
    cin >> n;
    po[0][0] = 1;
    po[1][0] = 1;
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i <= 1e6; i++) {
            po[j][i] = (po[j][i - 1] * 1ll * B[j]) % MOD;
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        h[i] = getHash(s[i]);
        f[h[i]].pb(i);
    }
    int nb = 0;
    for (auto &u : f) {
        if (u.se.size() >= 4) {
            cout << "YES\n";
            for (int i = 0; i < 4; i++) {
                cout << u.se[i] + 1 << " ";
            }
            return;
        }
        if (u.se.size() >= 2) {
            nb++;
        }
    }
    if (nb >= 2) {
        nb = 2;
        cout << "YES\n";
        vector<int> tmp[2];
        for (auto &u : f) {
            if (!nb) break;
            if (u.se.size() >= 2) {
                for (int i = 0; i < 2; i++) {
                    tmp[nb - 1].pb(u.se[i]);
                }
                nb--;
            }
        }
        cout << tmp[0][0] + 1 << " " << tmp[1][0] + 1 << " " << tmp[0][1] + 1
             << " " << tmp[1][1] + 1 << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int hs0 = (h[i].fi + 0ll + (po[0][s[i].size()] * 1ll * h[j].fi) % MOD) % MOD;
            int hs1 = (h[i].se + 0ll + (po[1][s[i].size()] * 1ll * h[j].se) % MOD) % MOD;
            f2[{hs0, hs1}].pb({i, j});
        }
    }
    for (auto &u : f2) {
        pair<int, int> p1 = u.se[0];
        for (auto &p : u.se) {
            if (p.fi == p1.fi || p.fi == p1.se || p.se == p1.fi ||
                p.se == p1.se) {
                continue;
            }
            cout << "YES\n";
            cout << p1.fi + 1 << " " << p1.se + 1 << " " << p.fi + 1 << " "
                 << p.se + 1 << endl;
            return;
        }
    }
    cout << "NO\n";
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
