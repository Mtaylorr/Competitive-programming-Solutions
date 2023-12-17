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

int n;
vector<pair<pair<ll, ll>, int>> v[N];
ll x;
int k;
int idx[N];
void test_case() {
    cin >> x >> k;
    set<pair<pair<ll, ll>, int>> st;
    for (int i = 0; i < k; i++) {
        int l;
        int y;
        cin >> l;
        ll mn = 0;
        ll sm = 0;
        while (l--) {
            cin >> y;
            sm += y;
            if (sm >= 0) {
                v[i].pb({{-mn, sm}, i});
                sm = 0;
                mn = 0;
            } else {
                mn = min(mn, sm);
            }
        }
        if (v[i].size()) {
            st.insert(v[i][0]);
        }
    }
    ll ans = x;
    pair<pair<ll, ll>, int> p;
    while (!st.empty()) {
        p = *st.begin();
        st.erase(st.begin());
        if (p.fi.fi <= x) {
            x += p.fi.se;
            int i = p.se;
            idx[i]++;
            if (idx[i] < v[i].size()) {
                st.insert({v[i][idx[i]]});
            }
        } else {
            break;
        }
        ans = max(ans, x);
    }
    cout << ans;
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
