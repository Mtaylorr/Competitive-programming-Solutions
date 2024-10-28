//
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

string s;
int k;
string ans;
// unordered_set<string> st[30];

void backtrack(int p, int k) {
    if (p >= s.size()) {
        ans = max(ans, s);
        return;
    }
    // if (st[k].count(s)) return;
    // st[k].insert(s);
    if (s.substr(0, p) < ans.substr(0, p)) return;
    if (k == 0) return;
    vector<int> ord;
    for (int j = p; j < s.size(); j++) {
        ord.pb(j);
    }
    sort(all(ord), [&](int &x, int &y) { return s[x] < s[y]; });
    for (auto &j : ord) {
        swap(s[j], s[p]);
        ans = max(ans, s);
        backtrack(p + 1, k - (p != j));
        swap(s[j], s[p]);
    }
}

void test_case() {
    cin >> s >> k;
    if (k >= s.size() - 1) {
        sort(rall(s));
        cout << s << endl;
        return;
    }
    ans = s;
    backtrack(0, k);
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
