// https://codeforces.com/contest/2209/problem/E

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

const int Z_N = N;
struct ZAlgo {
    int Z[Z_N];
    void run(string& s) {
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
        Z[0] = n;
    }
} z_algo;

int n, q;
string s;
void test_case() {
    cin >> n >> q;
    cin >> s;

    while (q--) {
        string t;
        int l, r;
        cin >> l >> r;
        l--, r--;
        t = s.substr(l, r - l + 1);
        z_algo.run(t);
        int target = t.size();

        ll ans = 1;
        stack<pair<int, int> > st;
        st.push({1, t.size()});
        for (int i = 1; i < t.size(); i++) {
            while (st.top().second < i) {
                st.pop();
            }
            if (z_algo.Z[i] >= 1) {
                int p = st.top().first;
                st.push({p + 1, i + z_algo.Z[i]});
            }
            while (st.top().second-1 < i) {
                st.pop();
            }
            // dbg(i, st.top().first, z_algo.Z[i]);
            ans += st.top().first;
        }
        // assert(target == 0);
        cout << ans << endl;
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
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
