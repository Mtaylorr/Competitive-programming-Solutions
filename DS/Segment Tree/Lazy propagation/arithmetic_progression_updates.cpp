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

int tree[4 * N], lazy_cnt[4 * N], lazy_st[4 * N];
int a[N];
int n;

void build(int id = 0, int ns = 0, int ne = n - 1) {
    lazy_cnt[id] = lazy_st[id] = 0;
    if (ns == ne) {
        tree[id] = a[ns];
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    tree[id] = tree[l] + tree[r];
}

void unlazy(int id, int ns, int ne) {
    if (lazy_cnt[id] == 0) return;
    int sz = ne - ns + 1;
    tree[id] += lazy_st[id] * sz + ((sz * (sz + 1)) / 2) * lazy_cnt[id];
    if (ns != ne) {
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        int lsz = md - ns + 1;
        lazy_cnt[l] += lazy_cnt[id];
        lazy_cnt[r] += lazy_cnt[id];
        lazy_st[l] += lazy_st[id];
        lazy_st[r] += lazy_st[id] + lsz * lazy_cnt[id];
    }
    lazy_cnt[id] = lazy_st[id] = 0;
}

void upd(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    unlazy(id, ns, ne);
    if (ns > qe || qs > ne) return;
    if (qs <= ns && qe >= ne) {
        lazy_cnt[id] = 1;
        lazy_st[id] = ns - qs;
        unlazy(id, ns, ne);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(qs, qe, l, ns, md);
    upd(qs, qe, r, md + 1, ne);
    tree[id] = tree[l] + tree[r];
}

int query(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    unlazy(id, ns, ne);
    if (ns > qe || qs > ne) {
        return 0;
    }
    if (qs <= ns && qe >= ne) {
        return tree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return query(qs, qe, l, ns, md) + query(qs, qe, r, md + 1, ne);
}

int b[N];

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    build();
    int q;
    cin >> q;
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 0) {
            int ans=0;
            for(int i=l;i<=r;i++){
                ans+=b[i];
            }
            cout << query(l, r) <<" "<< ans << endl;;

        } else {
            upd(l, r);
            for (int i = l; i <= r; i++) {
                b[i] += (i - l + 1);
            }
        }
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
