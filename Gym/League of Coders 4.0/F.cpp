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
int a[N];
const int MAXRT = N * 30;
template <typename T>
class DynSegTree {
   public:
    T vals[MAXRT];
    int freq[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    T defalt_value = 0;

    void init() { ndcnt = 0; }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    T mrg(T u, T v) { return (u ^ v); }

    T getval(int u) {
        if (u != -1) {
            return vals[u];
        }
        // define here the default value
        return defalt_value;
    }

    T getfreq(int u) {
        if (u != -1) {
            return freq[u];
        }
        // define here the default value
        return 0;
    }

    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = defalt_value;
        freq[ndcnt] = 0;
        return ndcnt++;
    }
    void pull_up(int &id) {
        vals[id] = mrg(getval(lch[id]), getval(rch[id]));
        freq[id] = getfreq(lch[id]) + getfreq(rch[id]);
    }

    void apply(int old_idx, int new_idx, T v) {
        vals[new_idx] = mrg(v, getval(old_idx));
        freq[new_idx] = 1 + getfreq(old_idx);
    }

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

    int firstOnCondition(int lnd, int rnd, int qs, int qe, int l, int r, int k) {
        if (qs > r || qe < l) return 0;
        if (l == r) {
            if (k % 2) return l;
            return 0;
        }
        int md = l + (r - l) / 2;
        int lsz = getfreq(left(rnd)) - getfreq(left(lnd));
        if (lsz >= k) {
            return firstOnCondition(left(lnd), left(rnd), qs, qe, l, md, k);
        }
        int lans = getval(left(rnd)) ^ getval(left(lnd));

        return lans ^ firstOnCondition(right(lnd), right(rnd), qs, qe, md + 1, r, k - lsz);
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
DynSegTree<int> sg;
int roots[N];
void test_case() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int lb = 0;
    int ub = (1 << 30) - 1;
    sg.init();
    roots[0] = sg.addnode();
    for (int i = 1; i <= n; i++) {
        roots[i] = sg.modify(roots[i - 1], a[i], lb, ub, 0, a[i]);
    }
    int l, r, k;
    while (q--) {
        cin >> l >> r >> k;
        if (r - l + 1 <= k) {
            int ans = sg.query(roots[r], lb, ub, lb, ub) ^ sg.query(roots[l - 1], lb, ub, lb, ub);
            cout << ans << endl;
        } else {
            cout << sg.firstOnCondition(roots[l - 1], roots[r], lb, ub, lb, ub, k) << endl;
        }
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
