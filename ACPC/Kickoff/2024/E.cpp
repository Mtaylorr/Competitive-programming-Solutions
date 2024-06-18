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

const int B_TRIE = 2;
const int L_TRIE = 30;  // only for binary trie, L is the maximum bit +1
const int N_TRIE = 2e7;

struct TrieNode {
    int nxt[B_TRIE];
    int isEnd;
    int cnt;
    int a;
    int dp = 0;
    int b = 0;
    void init() {
        memset(nxt, -1, sizeof(nxt));
        cnt = 0;
        isEnd = -1;
    }

    TrieNode() { init(); }
};

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

    void pull_up(int id, int b, int bit) {
        nodes[id].dp = (1ll << 30) - 1;
        nodes[id].a = bit;
        int &l = nodes[id].nxt[0];
        int &r = nodes[id].nxt[1];
        if (l != -1 && nodes[l].cnt) {
            nodes[id].a += nodes[l].a;
        } else if (r != -1 && nodes[r].cnt) {
            nodes[id].a += nodes[r].a;
        }
        if (b == -1 && nodes[id].cnt >= 2) {
            nodes[id].dp = 0;
            return;
        }
        if (l != -1) {
            nodes[id].dp = min(nodes[id].dp, nodes[l].dp);
        }
        if (r != -1) {
            nodes[id].dp = min(nodes[id].dp, nodes[r].dp);
        }
        // dbg(id, l, r, b, nodes[id].cnt);
        if (l != -1 && r != -1 && nodes[l].cnt >= 1 && nodes[r].cnt >= 1) {
            // dbg(nodes[id].dp);
            nodes[id].dp = min(nodes[id].dp, nodes[l].a ^ nodes[r].a);
        }
    }
    void ins(int cur, int b, int val, int ad, int bit) {
        if (b == -1) {
            pull_up(cur, b, bit);
            return;
        }
        int id = (val >> b) & 1;
        int &nx = nodes[cur].nxt[id];
        if (nx == -1) nx = addnode();
        nodes[nx].cnt += ad;
        ins(nx, b - 1, val, ad, id << b);
        pull_up(cur, b, bit);
    }
} trie;

int tree[2 * N];
int dptree[2 * N];
int n;
int a[N];
void upd(int i, int ns, int ne, int id, int ad) {
    trie.ins(tree[id], L_TRIE, a[i], ad, 0);
    dptree[id] = trie.nodes[tree[id]].dp;
    if (ns == ne) {
        return;
    }
    int md = (ns + ne) / 2;
    int l = 2 * id + 1;
    int r = l + 1;
    if (i <= md) {
        upd(i, ns, md, l, ad);
    } else {
        upd(i, md + 1, ne, r, ad);
    }
    dptree[id] = min({trie.nodes[tree[id]].dp, dptree[2 * id + 1], dptree[2 * id + 2]});
}

void test_case() {
    trie.init();
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        tree[i] = trie.addnode();
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        upd(i, 0, n - 1, 0, 1);
    }
    int q;
    cin >> q;
    int t, l, r;
    while (q--) {
        cin >> t >> l >> r;
        if (t == 1) {
            l--, r--;
            int id = 0;
            int ns = 0;
            int ne = n - 1;
            int tt = 0;
            while (ns != l || ne != r) {
                int md = (ns + ne) / 2;
                if (r <= md) {
                    ne = md;
                    id = 2 * id + 1;
                } else {
                    ns = md + 1;
                    id = 2 * id + 2;
                }
            }
            cout << dptree[id] << endl;
        } else {
            l--;
            upd(l, 0, n - 1, 0, -1);
            a[l] = r;
            upd(l, 0, n - 1, 0, 1);
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
