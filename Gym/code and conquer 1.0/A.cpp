// statement:
// given an array of n integers and q queries , for each query print the sum
// of last positions - first position for all distinct elements between l and r

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
const int N = 5e5 + 5;

const int MAXRT = N * 21;
template <typename T>
class DynSegTree {
   public:
    T vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    T defalt_value = 0;

    void init() { ndcnt = 0; }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    T mrg(T u, T v) { return (u + v); }

    T getval(int u) {
        if (u != -1) {
            return vals[u];
        }
        // define here the default value
        return defalt_value;
    }

    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = defalt_value;
        return ndcnt++;
    }
    void pull_up(int &id) { vals[id] = mrg(getval(lch[id]), getval(rch[id])); }

    void apply(int old_idx, int new_idx, T v) { vals[new_idx] = mrg(v, getval(old_idx)); }

    template <typename... M>
    int modify(int cur, int p, int l, int r, bool inplace, const M &...v) {
        if (l == r) {
            int idx = cur;
            if (cur == -1 || !inplace) {
                idx = addnode();
            }
            apply(cur, idx, v...);
            return idx;
        }
        int md = l + (r - l) / 2;
        int idx = cur;
        if (cur == -1 || !inplace) {
            idx = addnode();
        }
        if (p <= md) {
            lch[idx] = modify(left(cur), p, l, md, inplace, v...);
            rch[idx] = right(cur);
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), p, md + 1, r, inplace, v...);
        }
        pull_up(idx);
        return idx;
    }

    int firstOnCondition(int nd, int qs, int qe, int l, int r, function<bool(int)> ch) {
        if (qs > r || qe < l) return -1;
        if (qs <= l && qe >= r) {
            if (ch(getval(nd))) {
                return -1;
            }
        }
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int x = firstOnCondition(left(nd), qs, qe, l, md, ch);
        if (x == -1) {
            return firstOnCondition(right(nd), qs, qe, md + 1, r, ch);
        }
        return x;
    }

    T query(int nd, int qs, int qe, int l, int r) {
        if (qs <= l && qe >= r) {
            return getval(nd);
        }
        int md = l + (r - l) / 2;
        if (qe <= md) {
            return query(left(nd), qs, qe, l, md);
        } else {
            if (qs > md) {
                return query(right(nd), qs, qe, md + 1, r);
            } else {
                return mrg(query(left(nd), qs, qe, l, md), query(right(nd), qs, qe, md + 1, r));
            }
        }
    }
};
DynSegTree<ll> sg;

int n, a[N], q;
int pos[N];
int roots[N];
ll x, y;
void test_case() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sg.init();
    roots[0] = sg.addnode();
    memset(pos, -1, sizeof(pos));
    for (int i = 1; i <= n; i++) {
        int lstpos = pos[a[i]];
        if (lstpos == -1) {
            roots[i] = roots[i - 1];
        } else {
            roots[i] = sg.modify(roots[i - 1], lstpos, 1, n, 0, -lstpos + i);
        }
        pos[a[i]] = i;
    }
    long long ans = 0;
    while (q--) {
        cin >> x >> y;
        x ^= ans;
        y ^= ans;
        x %= n;
        x++;
        y %= n;
        y++;
        if (x > y) {
            swap(x, y);
        }
        ans = sg.query(roots[y], x, y, 1, n);
        cout << ans << endl;
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
