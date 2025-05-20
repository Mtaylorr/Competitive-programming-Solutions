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

const int MAXRT = N * 30;
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

    int firstOnCondition(int nd, int qs, int qe, int l, int r, int &t) {
        if (qs > r || qe < l) return -1;
        if (qs <= l && qe >= r) {
            int sum = (r - l + 1) * 8 - getval(nd);
            // dbg(l, r, sum, getval(nd));
            if (sum < t) {
                t -= sum;
                return -1;
            }
        }
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int x = firstOnCondition(left(nd), qs, qe, l, md, t);
        if (x == -1) {
            return firstOnCondition(right(nd), qs, qe, md + 1, r, t);
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
DynSegTree<int> sg;
int n, m, q;

int roots[11][11];
map<int, int> vacation[N];

void upd(int a, int x, int y) {
    for (int i = 0; i < m; i++) {
        int l = i;
        int r = a;
        if (l == r) continue;
        if (l > r) {
            swap(l, r);
        }
        if (vacation[l][x] == 3 || vacation[r][x] == 3) continue;
        if (vacation[l][x] == y || vacation[r][x] == y) continue;
        roots[l][r] = sg.modify(roots[l][r], x, 0, 5 * n, 1, 4);
    }
    vacation[a][x] |= y;
}

void test_case() {
    cin >> n >> m >> q;
    sg.init();
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            roots[i][j] = sg.addnode();
        }
    }
    int t, a, b, x, y;
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> a >> x;
            --a;
            x--;
            if (x % 7 >= 5) continue;
            x -= 2 * (x / 7);
            upd(a, x, 1);
            upd(a, x, 2);
        } else if (t == 2) {
            cin >> a >> x >> y;
            x--;
            if (x % 7 >= 5) continue;
            --a;
            x -= 2 * (x / 7);
            upd(a, x, y);
        } else {
            cin >> a >> b >> x >> t;
            x--;
            a--, b--;
            if (a > b) {
                swap(a, b);
            }
            while (x % 7 >= 5) {
                x++;
            }
            x -= 2 * (x / 7);
            int idx = sg.firstOnCondition(roots[a][b], x, 5 * n, 0, 5 * n, t);
            if (idx == -1) {
                cout << -1 << endl;
                continue;
            }
            int real_value = (idx / 5) * 2 + idx + 1;
            if (real_value <= 7 * n) {
                cout << real_value << endl;
            } else {
                cout << -1 << endl;
            }
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
