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
const int B = 1009;
int hpo[N];
int po[N];
int freq[20];
string ans = "";
string cur;
string s;
int n;
int rem;
int cmd = 0;
int maxiter = 1e6;
unordered_set<int> st;
void backtrack(int p) {
    if (ans.size()) return;
    if (p == -1) {
        if (cmd == 0) {
            ans = cur;
            return;
        }
        return;
    }
    int h = 0;
    for (int i = 0; i < 7; i++) {
        h = (h + (hpo[i] * 1ll * (freq[i] + freq[i + 7])) % MOD) % MOD;
    }
    h = (h + (hpo[10] * 1ll * cmd) % MOD) % MOD;
    if (st.count(h)) return;
    st.insert(h);
    maxiter--;
    if (maxiter < 0) {
        cout << -1;
        exit(0);
    }
    for (int i = 9; i >= 0; i--) {
        if (i == 0 && p == n - 1) continue;
        if (!freq[i]) continue;
        if (ans.size()) return;
        cur += char('0' + i);
        int initial = cmd;
        cmd = (cmd + po[p] * i) % 7;
        freq[i]--;
        backtrack(p - 1);
        freq[i]++;
        cur.pop_back();
        cmd = initial;
    }
}

void test_case() {
    cin >> s;
    n = s.size();
    rem = n;
    cur = "";
    po[0] = 1;
    hpo[0] = 1;
    for (int i = 1; i <= 10; i++) {
        hpo[i] = (hpo[i - 1] * 1ll * B) % MOD;
    }
    for (int i = 1; i <= n; i++) {
        po[i] = (po[i - 1] * 1ll * 10) % 7;
    }
    for (auto &c : s) {
        freq[c - '0']++;
    }
    backtrack(n - 1);
    if (ans == "") {
        cout << "-1";
        return;
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
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
