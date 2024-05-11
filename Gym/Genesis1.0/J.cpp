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
const int N = 2e6 + 5;

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) { return (upper_bound(all(values), x) - values.begin()) - 1; }
    int greaterThanOrEqual(ll x) { return (lower_bound(all(values), x) - values.begin()); }
    ll decompress(int p) { return values[p]; }
} c1, c2;

int l[N], r[N], c[N];
vector<int> ids[N];
int n, m[N];

struct node {
    ll sum = 0;
    int nxt;
    int switches;
    // define states here
    bool has_lazy;
    int lazy = 0;
    node() {
        sum = 0;
        nxt = -1;
        switches = 0;
        // initialize states here
        has_lazy = false;
        lazy = 0;
    }
    void apply(int ns, int ne, ll v) {
        // update value
        // update lazy
        has_lazy = 0;
    }

    void apply(int ns, int ne, ll v, int nbswitches, int idx) {
        // update value
        // dbg(ns, ne, v, sum);
        if (v > sum) {
            sum = v;
            switches = nbswitches;
            nxt = idx;
        } else if (sum == v) {
            if (switches > nbswitches) {
                switches = nbswitches;
                nxt = idx;
            }
        }

        // update lazy
        has_lazy = 0;
    }
    void clear_lazy() {
        has_lazy = 0;
        lazy = 0;
    }
};

struct SegTree {
    vector<node> tree;
    int n;
    node mrg(const node &l, const node &r) {
        node res;
        // merge nodes
        if (l.sum > r.sum || (l.sum == r.sum && l.switches < r.switches)) {
            res.sum = l.sum;
            res.switches = l.switches;
            res.nxt = l.nxt;
        } else {
            res.sum = r.sum;
            res.switches = r.switches;
            res.nxt = r.nxt;
        }
        return res;
    }
    void pull(int id, int ns, int ne) {
        int l = 2 * id + 1;
        int r = l + 1;
        tree[id] = mrg(tree[l], tree[r]);
    }

    void push(int id, int ns, int ne) {
        if (tree[id].has_lazy && ns != ne) {
            int l = 2 * id + 1;
            int r = l + 1;
            int md = ns + (ne - ns) / 2;
            tree[l].apply(ns, md, tree[id].lazy);
            tree[r].apply(md + 1, ne, tree[id].lazy);
            tree[id].clear_lazy();
        }
    }
    template <typename M>
    void build(int id, int ns, int ne, const vector<M> &v) {
        if (ns == ne) {
            tree[id].apply(ns, ne, v[ns]);
            return;
        }
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        build(l, ns, md, v);
        build(r, md + 1, ne, v);
        pull(id, ns, ne);
    }
    void build(int id, int ns, int ne) {
        if (ns == ne) {
            return;
        }
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        build(l, ns, md);
        build(r, md + 1, ne);
        pull(id, ns, ne);
    }
    node query(int qs, int qe, int id, int ns, int ne) {
        if (qs <= ns && qe >= ne) {
            return tree[id];
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        node res;
        if (qe <= md) {
            res = query(qs, qe, l, ns, md);
        } else {
            if (qs > md) {
                res = query(qs, qe, r, md + 1, ne);
            } else {
                node rl = query(qs, qe, l, ns, md);
                node rr = query(qs, qe, r, md + 1, ne);
                res = mrg(rl, rr);
            }
        }
        pull(id, ns, ne);
        return res;
    }

    int getFirstOnCondition(int qs, int qe, int dir, int id, int ns, int ne, int k) {
        if (qs > ne || qe < ns) return -1;
        if (qs <= ns && qe >= ne) {
            // check condition on interval
        }
        if (ns == ne) {
            return ns;
        }
        push(id, ns, ne);
        int p;
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        if (dir == 0)
            p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        else
            p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
        if (p == -1) {
            if (dir == 0)
                p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
            else
                p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        }
        pull(id, ns, ne);
        return p;
    }

    template <typename... M>
    void update(int qs, int qe, int id, int ns, int ne, const M &...v) {
        if (qs > ne || qe < ns) return;
        if (qs <= ns && qe >= ne) {
            tree[id].apply(ns, ne, v...);
            return;
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        update(qs, qe, l, ns, md, v...);
        update(qs, qe, r, md + 1, ne, v...);
        pull(id, ns, ne);
    }
    SegTree(int _n) {
        n = _n;
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }
    template <typename M>
    SegTree(const vector<M> &v) {
        n = v.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }
    node get(int qs, int qe) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        return query(qs, qe, 0, 0, n - 1);
    }

    node get(int p) {
        assert(p >= 0 && p <= n - 1);
        return query(p, p, 0, 0, n - 1);
    }
    template <typename... M>
    int getFirstOnCondition(int qs, int qe, int dir, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1 && dir >= 0 && dir <= 1);
        return getFirstOnCondition(qs, qe, dir, 0, 0, n - 1, v...);
    }
    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        update(qs, qe, 0, 0, n - 1, v...);
    }
};
ll dp[N];
ll sum[N];
int sw[N];
int nxt[N];

void test_case() {
    cin >> n;
    c1.init();
    c2.init();
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i] >> m[i] >> c[i];
        r[i]++;
        c1.add(l[i]);
        c1.add(r[i]);
        c2.add(m[i]);
    }
    c1.run();
    c2.run();
    int p = c2.n;
    for (int i = 0; i < n; i++) {
        l[i] = c1.compress(l[i]);
        r[i] = c1.compress(r[i]);
        m[i] = c2.compress(m[i]);
        ids[m[i]].pb(i);
    }
    for (int i = 0; i < p; i++) {
        sort(all(ids[p]), [](int &x, int &y) { return l[x] < l[y]; });
    }
    SegTree sg = SegTree(c1.n);
    ll ansum = 0;
    int anssw = 0;
    int ansp = 0;
    for (int j = 0; j < p; j++) {
        node nd = node();
        for (auto &i : ids[j]) {
            node rs = sg.get(0, l[i]);
            rs.switches++;
            nd = sg.mrg(nd, rs);
            nd.sum += c[i];
            sum[i] = nd.sum;
            sw[i] = nd.switches;
            nxt[i] = nd.nxt;
            if (ansum < nd.sum) {
                ansum = nd.sum;
                anssw = sw[i];
                ansp = i;
            }
            nd.nxt=i;
        }
        for (auto &i : ids[j]) {
            sg.upd(r[i], r[i], sum[i], sw[i], i);
        }
    }
    cout << ansum << " " << anssw << endl;
    vector<int> path;
    while(ansp!=-1){
        path.pb(ansp);
        ansp=nxt[ansp];
    }
    reverse(all(path));
    cout << path.size() << endl;
    for(auto &u:path){
        cout << u+1 << " ";
    }
    cout << endl;
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
