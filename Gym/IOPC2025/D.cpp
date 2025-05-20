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
ll t[N];
string s[N];
string tag[N];
vector<pair<ll, int> > st[10];
int id[N];
map<string, int> code;
ll ans[N];
void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        ans[i] = t[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> tag[i];
        if (code.count(tag[i]) == 0) {
            code[tag[i]] = cnt++;
        }
    }
    vector<int> ord;
    for (int i = 0; i < n; i++) {
        ord.pb(i);
    }
    sort(all(ord), [](int &x, int &y) { return s[x] < s[y]; });
    for (int i = 0; i < n; i++) {
        id[ord[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        st[code[tag[i]]].push_back({t[i], id[i]});
    }
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;

        int t;
        cin >> t;
        if (code.count(s) == 0) continue;
        int p = code[s];
        if (st[p].size() == 0) continue;
        sort(all(st[p]));
        int nb = 0;
        ll rem = t;
        for (int j = 0; j < st[p].size(); j++) {
            nb++;
            if (nb == st[p].size()) break;
            ll nx = st[p][j + 1].fi - st[p][j].fi;
            if (rem >= nx * nb) {
                rem -= nx * nb;
                for (int k = 0; k <= j; k++) {
                    st[p][k].fi = st[p][j + 1].fi;
                }
                continue;
            } else {
                break;
            }
        }
        sort(all(st[p]));
        for (int i = 0; i < nb; i++) {
            st[p][i].fi += rem / nb + ((rem % nb) > i);
        }
        for (auto &u : st[p]) {
            ans[ord[u.se]] = u.fi;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
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
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
