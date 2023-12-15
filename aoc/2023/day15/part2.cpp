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

vector<string> split(string &s, string delimiter) {
    size_t pos = 0;
    string token;
    vector<string> ans;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        if (token != "") ans.pb(token);
        s.erase(0, pos + delimiter.length());
    }
    if (s != "") {
        ans.pb(s);
    }
    return ans;
}
string s;
int solve(string &s) {
    int r = 0;
    for (auto &c : s) {
        r += int(c);
        r *= 17;
        r %= 256;
    }
    return r;
}

map<string, pair<int, int> > st[N];

void test_case() {
    ll ans = 0;
    int id = 0;
    while (cin >> s) {
        vector<string> t = split(s, ",");
        for (auto &u : t) {
            id++;
            if (u[u.size() - 1] == '-') {
                // remove
                u.pop_back();
                int h = solve(u);
                if (st[h].count(u)) {
                    st[h].erase(u);
                }
            } else {
                // add
                char focal = u[u.size() - 1];
                u.pop_back();
                u.pop_back();
                int h = solve(u);
                if (st[h].count(u)) {
                    st[h][u].se = focal - '0';
                } else {
                    st[h][u] = {id, focal - '0'};
                }
            }
        }
    }
    for (int i = 0; i < 256; i++) {
        vector<pair<int, int> > v;
        for (auto &u : st[i]) {
            v.pb(u.se);
        }
        if (v.size() == 0) continue;
        sort(all(v));
        for (int j = 0; j < v.size(); j++) {
            ans += (i + 1) * (j + 1) * (v[j].se);
        }
    }
    cout << ans << endl;
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
