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

ll tree[4 * N];
ll val[N];
multiset<ll> st[N];
int t, d;
ll b;
int n;
void upd(int p, ll v, int id = 0, int ns = 0, int ne = 1e6) {
    if (ns == ne) {
        tree[id] = v;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    if (p <= md) {
        upd(p, v, l, ns, md);
    } else {
        upd(p, v, r, md + 1, ne);
    }
    tree[id] = max(tree[l], tree[r]);
}

void update(int x) {
    if (x == 0) return;
    if (st[x].size() == 0) {
        upd(x, 0);
        val[x] = 0;
        update(x / 2);
        return;
    }
    ll sm = -(*st[x].begin());
    ll r = 0;
    if (2 * x <= 1e6) {
        r = val[2 * x];
    }
    if (2 * x + 1 <= 1e6) {
        r = max(r, val[2 * x + 1]);
    }
    val[x] = max({sm, sm + r});
    val[x] = max(val[x], 0ll);
    upd(x, val[x]);
    update(x / 2);
}

void test_case() {
    cin >> n;
    while (n--) {
        cin >> t >> d >> b;
        if (t == 1) {
            st[d].insert(-b);
        } else {
            st[d].erase(st[d].find(-b));
        }
        update(d);
        cout << tree[0] << endl;
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
