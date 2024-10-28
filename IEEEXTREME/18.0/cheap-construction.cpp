//https://csacademy.com/ieeextreme18/task/cheap-construction/
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

class DSUWithRollBack {
   public:
    struct dsu_save {
        int u, rnku, v, rnkv;
        bool ex;
        dsu_save() {}

        dsu_save(int _u, int _rnku, int _v, int _rnkv, bool _ex) : u(_u), rnku(_rnku), v(_v), rnkv(_rnkv), ex(_ex) {}
    };
    vector<int> id, sz, rnk;
    stack<dsu_save> op;
    int comps;
    void init(int n) {
        comps = n;
        id.assign(n, 0);
        sz.assign(n, 0);
        rnk.assign(n, 0);
        while (!op.empty()) {
            op.pop();
        }
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    bool uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) {
            op.push(dsu_save(u, rnk[u], v, rnk[v], 0));
            return 0;
        }
        if (rnk[v] > rnk[u]) swap(v, u);
        op.push(dsu_save(u, rnk[u], v, rnk[v], 1));
        id[v] = u;
        sz[u] += sz[v];
        comps--;
        if (rnk[u] == rnk[v]) rnk[u]++;
        return 1;
    }

    void rollback() {
        if (op.empty()) {
            return;
        }
        dsu_save x = op.top();
        op.pop();
        if (x.ex == 0) {
            return;
        }
        comps++;
        id[x.u] = x.u;
        id[x.v] = x.v;
        rnk[x.u] = x.rnku;
        rnk[x.v] = x.rnkv;
        sz[x.u] -= sz[x.v];
    }
} dsu_rb;

const int B_TRIE = 26;
const int N_TRIE = 2500000;
int ans[N];

struct TrieNode {
    unordered_map<int, int> nxt;
    vector<pair<int, int>> edges;
    int isEnd;
    int cnt;
    void init() {
        cnt = 0;
        isEnd = -1;
        edges.clear();
    }
    TrieNode() { init(); }
};
int n;
string s;

string rs = "";
class Trie {
   public:
    TrieNode nodes[N_TRIE];
    int ndcnt = 0;
    int addnode() {
        nodes[ndcnt].init();
        return ndcnt++;
    }
    void init() {
        ndcnt = 0;
        addnode();
    }

    void ins(string &s, int p = 1, int from = 0, int to = -1) {
        // s is the string to add to the trie
        // p is the index of the string if we want to get it after
        // from is where to start to the string from
        // to is the until when we need to add the string
        int cur = 0;
        if (to == -1) to = sz(s) - 1;
        for (int i = from; i <= to; i++) {
            // To change if the characters change
            int id = s[i] - 'a';
            int nx;
            if (nodes[cur].nxt.count(id) == 0) {
                nx = nodes[cur].nxt[id] = addnode();
            } else {
                nx = nodes[cur].nxt[id];
            }

            nodes[nx].cnt++;
            if (i != from) {
                nodes[nx].edges.push_back({from, i});
            }

            cur = nx;
        }
        nodes[cur].isEnd = p;
    }

    void traverse(int cur, int le = 0) {
        sort(all(nodes[cur].edges));
        int comps = n;
        int l = -1;
        int r = -1;
        for (auto &u : nodes[cur].edges) {
            if (u.fi > r) {
                comps -= (r - l);
                l = u.fi;
                r = u.se;
            } else {
                r = max(r, u.se);
            }
        }
        // dbg(cur, le, comps);
        comps -= (r - l);
        if (le != 0) ans[comps] = min(ans[comps], le);
        for (int i = 0; i < 26; i++) {
            if (nodes[cur].nxt.count(i)) {
                int nx = nodes[cur].nxt[i];
                rs += char('a' + i);
                traverse(nx, le + 1);
                rs.pop_back();
            }
        }
    }
} trie;

const int MAX_SUFF = 5005 + 5;
const int LOGSPT = 15;
template <typename T>
class SPT {
   public:
    vector<T> spt[LOGSPT];
    int po[LOGSPT];
    vector<int> lg;
    int n;

    T mrg(T &x, T &y) { return min(x, y); }

    void init(vector<T> &v) {
        n = v.size();
        lg.assign(n + 1, 0);
        po[0] = 1;
        for (int i = 0; i < LOGSPT; i++) {
            spt[i].assign(n, 0);
            if (i > 0) po[i] = 2 * po[i - 1];
        }
        lg[0] = -1;
        for (int i = 1; i <= n; i++) {
            lg[i] = 1 + lg[i / 2];
        }
        for (int i = 0; i < n; i++) {
            spt[0][i] = v[i];
        }
        for (int b = 1; po[b] <= n; b++) {
            for (int i = 0; i + po[b] <= n; i++) {
                spt[b][i] = mrg(spt[b - 1][i], spt[b - 1][i + po[b - 1]]);
            }
        }
    }
    T getLog(int l, int r) {
        int d = r - l + 1;
        T rs = 1e9;
        for (int i = LOGSPT - 1; i >= 0; i--) {
            if (po[i] <= d) {
                rs = mrg(rs, spt[i][l]);
                d -= po[i];
                l += po[i];
            }
        }
        return rs;
    }

    T getConstant(int l, int r) {
        int lg2 = lg[r - l + 1];
        return mrg(spt[lg2][l], spt[lg2][r - po[lg2] + 1]);
    }
};

class SuffixArray {
   public:
    int suff[MAX_SUFF], newsuff[MAX_SUFF];
    char s[MAX_SUFF];
    vector<int> lcp;
    int rnk[MAX_SUFF], newrnk[MAX_SUFF], bst[MAX_SUFF], bcnt;
    SPT<int> spt;
    int n;
    void buildSuffixArray() {
        iota(suff, suff + n, 0);
        bcnt = 0;
        sort(suff, suff + n, [this](int &x, int &y) { return s[x] < s[y]; });
        bst[0] = 0;
        rnk[suff[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (s[suff[i]] == s[suff[i - 1]]) {
                rnk[suff[i]] = bcnt;
            } else {
                bcnt++;
                bst[bcnt] = i;
                rnk[suff[i]] = bcnt;
            }
        }

        int cur = 1;
        do {
            auto cmp = [this, cur](int &x, int &y) { return mp(rnk[x], rnk[x + cur]) < mp(rnk[y], rnk[y + cur]); };
            newsuff[0] = suff[0];
            for (int i = 0; i < n; i++) {
                if (suff[i] - cur >= 0) {
                    int x = suff[i] - cur;
                    newsuff[bst[rnk[x]]++] = x;
                }
            }
            for (int i = 0; i < n; i++) {
                suff[i] = newsuff[i];
            }
            bcnt = 0;
            bst[0] = 0;
            newrnk[suff[0]] = 0;
            for (int i = 1; i < n; i++) {
                if (!cmp(suff[i - 1], suff[i])) {
                    newrnk[suff[i]] = bcnt;
                } else {
                    bcnt++;
                    bst[bcnt] = i;
                    newrnk[suff[i]] = bcnt;
                }
            }
            for (int i = 0; i < n; i++) {
                rnk[i] = newrnk[i];
            }
            cur *= 2;
        } while (bcnt != n - 1);
    }
    void buildLCP() {
        int cur = 0;
        lcp[0] = 0;
        for (int i = 0; i < n - 1; i++) {
            int j = suff[rnk[i] - 1];
            while (s[i + cur] == s[j + cur]) {
                cur++;
            }
            lcp[rnk[i]] = cur;
            if (cur) --cur;
        }
    };
    void init(string &t, bool spt_query = false) {
        for (int i = 0; i < t.size(); i++) {
            s[i] = t[i];
        }
        s[t.size()] = 0;
        n = t.size() + 1;
        memset(rnk, 0, 2 * n * sizeof(rnk[0]));
        lcp.assign(n + 1, 0);
        buildSuffixArray();
        buildLCP();
        if (spt_query) {
            spt.init(lcp);
        }
    }

    int getlcp(int x, int y) {
        // int l = rnk[x];
        // int r = rnk[y];
        int l = x;
        int r = y;
        if (l == r) {
            return n - x;
        }
        if (l > r) swap(l, r);
        return spt.getConstant(l + 1, r);
    }

    void print() {
        for (int i = 0; i < n; i++) {
            // printf("%s \n", s + suff[i]);
            // fflush(stdin);
            cout << suff[i] << " " << lcp[i] << endl;
        }
    }
} SA;

void test_case() {
    cin >> s;
    n = s.size();
    for (int i = 1; i <= n; i++) {
        ans[i] = 1e9;
    }
    SA.init(s, true);
    // SA.print();
    vector<int> tmp;
    for (int i = 1; i <= n; i++) {
        int sz = n - SA.suff[i];
        for (int le = SA.lcp[i] + 1; le <= sz; le++) {
            int l = i;
            int r = n;
            while (l < r) {
                int md = (l + r + 1) / 2;
                if (SA.getlcp(i, md) >= le) {
                    l = md;
                } else {
                    r = md - 1;
                }
            }
            r = l;
            l = i;
            tmp.clear();
            // dbg(SA.suff[i], le, l, r);
            for (int j = l; j <= r; j++) {
                tmp.push_back(SA.suff[j]);
            }
            sort(all(tmp));
            int comps = n;
            int lf = -1;
            int rg = -1;
            // cout << "-----------------" << endl;
            for (auto &u : tmp) {
                // dbg(u);
                // dbg(u, u + le - 1);
                if (u > rg) {
                    comps -= (rg - lf);
                    lf = u;
                    rg = u + le - 1;
                } else {
                    rg = max(rg, u + le - 1);
                }
            }
            // dbg(cur, le, comps);
            comps -= (rg - lf);
            // dbg(SA.suff[i], le, comps);
            if (le != 0) ans[comps] = min(ans[comps], le);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] <= n) {
            cout << ans[i] << " ";
        } else {
            cout << 0 << " ";
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
