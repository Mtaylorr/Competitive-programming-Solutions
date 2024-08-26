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

const int MOD = 998244353;
template <typename T, typename U>
int mul(T u, U v, int mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}
template <typename T, typename U>
int add(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}
template <typename T, typename U>
int sub(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}
template <typename T>
int powe(T u, ll v, int mod = MOD) {
    int ans = 1;
    int acc = u % mod;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}
template <typename T>
int inv(T u, int mod = MOD) {
    return powe(u, mod - 2, mod);
}

const int B = 263;

const int invB = inv(B);

int po[N], invpo[N];
int h[N];
void preprocess() {
    po[0] = invpo[0] = 1;
    for (int i = 1; i <= 1e6; i++) {
        po[i] = (po[i - 1] * 1ll * B) % MOD;
        invpo[i] = (invpo[i - 1] * 1ll * invB) % MOD;
    }
}

void buildHash(string &s) {
    for (int i = 1; i <= s.size(); i++) {
        int cur = s[i - 1];
        h[i] = (h[i - 1] + (po[i] * 1ll * cur) % MOD) % MOD;
    }
}

int getRangeHash(int l, int r) {
    int ans = (h[r] + 0ll + MOD - h[l - 1]) % MOD;
    return (ans * 1ll * invpo[l - 1]) % MOD;
}
int n;
string s[N];
set<int> st[N];
map<int, int> freq[N];
ll ans[N];
int q;

void manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
            if (i % 2 == 0) {
                if (p[i] % 2 == 1) {
                    int idx = (i - 1) / 2 + 1;
                    int sz = p[i] / 2 + 1;
                    int h = getRangeHash(idx, idx + sz - 1);
                    st[2 * sz - 1].insert(h);
                }
            } else {
                if (p[i] % 2 == 0) {
                    int idx = (i) / 2 + 1;
                    int sz = p[i] / 2;
                    int h = getRangeHash(idx, idx + sz - 1);
                    st[2 * sz].insert(h);
                }
            }
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
}
void manacher(string& s) {
    for (int i = 0; i <= s.size(); i++) {
        st[i].clear();
    }
    string t;
    for (auto c : s) {
        t += string("#") + c;
    }
    manacher_odd(t + "#");
    // dbg("--------------");
    for (int i = 0; i <= s.size(); i++) {
        for (auto &u : st[i]) {
            // dbg(i, u);
            freq[i][u]++;
        }
    }
}

void test_case() {
    cin >> n;
    int mxsz = 0;

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        mxsz = max(mxsz, (int)s[i].size());
    }
    for (int i = 0; i <= mxsz; i++) {
        freq[i].clear();
        ans[i]=0;
    }
    for (int i = 0; i < n; i++) {
        buildHash(s[i]);
        manacher(s[i]);
    }
    for (int i = 0; i <= mxsz; i++) {
        for (auto &u : freq[i]) {
            if (u.se == n) {
                ans[i] += 1;
            }
        }
    }
    int q;
    int x;
    cin >> q;
    while (q--) {
        cin >> x;
        if (x > mxsz) {
            cout << 0 << "\n";
        } else {
            cout << ans[x] << "\n";
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
    preprocess();
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
