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
int n, q;
int a[N], b[N];
int x[N], y[N];
set<int> distincts;
map<int, int> code;
vector<pair<int, int> > v;
int tree[N];
int m;
void upd(int x) {
    for (; x <= m; x += (x) & (-x)) tree[x]++;
}
int query(int x) {
    int rs = 0;
    for (; x; x -= (x) & (-x)) rs += tree[x];
    return rs;
}
int ans[N];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> a[i] >> b[i];
        distincts.insert(b[i]);
        v.pb({a[i], -(i + 1)});
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> x[i] >> y[i];
        distincts.insert(y[i]);
        v.pb({x[i], i + 1});
    }
    m = 1;
    for (auto &u : distincts) {
        code[u] = m++;
    }
    sort(all(v));
    for (auto u : v) {
        int p = u.second;
        if (p < 0) {
            p *= -1;
            p--;
            upd(code[b[p]]);
        } else {
            p--;
            ans[p] = query(code[y[p]]);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
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
