//https://codeforces.com/problemset/problem/526/D
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

const int KMP_N = N;
struct KMP {
    int F[KMP_N];

    int getNextLen(int len, char c, string &pat) {
        while (len && pat[len] != c) len = F[len - 1];
        if (pat[len] == c) len++;
        return len;
    }
    void run(string &pat) {
        F[0] = 0;
        for (int i = 1; i < pat.size(); i++) {
            F[i] = getNextLen(F[i - 1], pat[i], pat);
        }
    }

    void match(string &s, string &pat) {
        int len = 0;
        for (int i = 0; i < s.size(); i++) {
            len = getNextLen(len, s[i], pat);
            if (!pat[len]) printf("%d\n", i - len + 1);
        }
    }
} kmp;
const int Z_N = N;
struct ZAlgo {
    int Z[Z_N];
    void run(string &s) {
        Z[0] = 0;
        int l = 1, r = 1;
        int n = s.size();
        for (int i = 1; i < n; i++) {
            int x = Z[i - l];
            if (i + x >= r) {
                l = i;
                r = max(r, i);
                while (r < n && s[r - l] == s[r]) r++;
                Z[i] = r - l;
            } else {
                Z[i] = Z[i - l];
            }
        }
    }
} z_algo;

int n, k;
string s;
bool ans[N];
int sum[N];
void test_case() {
    cin >> n >> k;
    cin >> s;
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            cout << 1;
        }
        return;
    }
    kmp.run(s);
    z_algo.run(s);
    for (int i = 1; i < n; i++) {
        int x = kmp.F[i];
        int cur = i + 1;
        int y = cur - x;
        if (cur % y == 0) {
            int nb = cur / y;
            if (nb % k == 0) {
                sum[i]++;
                sum[i + 1]--;
            }

            if (nb % k == 0 && i + 1 < n) {
                int ns = y * (nb / k);
                int r = min(ns, z_algo.Z[i + 1]);
                sum[i + 1]++;
                sum[i + 1 + r]--;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            sum[i] += sum[i - 1];
        }
        if (sum[i]) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    //cin >> T;
    T=1;
    while (T--) {
        test_case();
    }
    return 0;
}
