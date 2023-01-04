//https://codeforces.com/problemset/problem/427/D

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

const int MAX_SUFF = 1e5 + 5;
namespace SA {
int suff[MAX_SUFF], newsuff[MAX_SUFF];
char s[MAX_SUFF];
int lcp[MAX_SUFF];
int rnk[N], newrnk[N], bst[N], bcnt;
int n;
void buildSuffixArray() {
    for (int i = 0; i < n; i++) {
        suff[i] = i;
    }
    bcnt = 0;
    sort(suff, suff + n, [](int &x, int &y) { return s[x] < s[y]; });
    bst[0] = 0;
    rnk[suff[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (s[suff[i]] == s[suff[i - 1]]) {
            rnk[suff[i]] = bcnt;
        } else {
            bcnt++;
            bst[bcnt] = i;
            rnk[suff[i]] = bcnt;
        }
    }
    int cur = 1;
    do {
        auto cmp = [cur](int &x, int &y) {
            return mp(rnk[x], rnk[x + cur]) < mp(rnk[y], rnk[y + cur]);
        };
        newsuff[0] = suff[0];
        for (int i = 0; i < n; i++) {
            if (suff[i] - cur >= 0) {
                int x = suff[i] - cur;
                newsuff[bst[rnk[x]]++] = x;
            }
        }
        for (int i = 0; i < n; i++) {
            suff[i] = newsuff[i];
        }
        bcnt = 0;
        bst[0] = 0;
        newrnk[suff[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (!cmp(suff[i - 1], suff[i])) {
                newrnk[suff[i]] = bcnt;
            } else {
                bcnt++;
                bst[bcnt] = i;
                newrnk[suff[i]] = bcnt;
            }
        }
        for (int i = 0; i < n; i++) {
            rnk[i] = newrnk[i];
        }
        cur *= 2;
    } while (bcnt != n - 1);
}

void buildLCP() {
    int cur = 0;
    lcp[0] = 0;
    for (int i = 0; i < n - 1; i++) {
        int j = suff[rnk[i] - 1];
        while (s[i + cur] == s[j + cur]) {
            cur++;
        }
        lcp[rnk[i]] = cur;
        if (cur) --cur;
    }
};
void init(string &t) {
    for (int i = 0; i < t.size(); i++) {
        s[i] = t[i];
    }
    s[t.size()] = 0;
    n = t.size() + 1;
    memset(rnk, 0, 2 * n * sizeof(rnk[0]));
    memset(lcp, 0, 2 * n * sizeof(lcp[0]));
    buildSuffixArray();
    buildLCP();
}
};  // namespace SA
string s2, s1;

void solve() {
    cin >> s1;
    int n = sz(s1);
    cin >> s2;
    s1 += "#";
    s1 += s2;
    SA::init(s1);
    int ans = 1e9;
    for (int i = 0; i + 1 < SA::n; i++) {
        bool c = SA::suff[i] < n;
        bool d = SA::suff[i + 1] < n;
        if (c != d) {
            int mx = 0;
            mx = max(mx, SA::lcp[i]);
            mx = max(mx, SA::lcp[i + 2]);
            if (mx + 1 <= SA::lcp[i + 1]) {
                ans = min(ans, mx + 1);
            }
        }
    }
    if (ans < 1e9) {
        cout << ans << endl;

    } else {
        cout << -1 << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
