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
const int N_TRIE = N * L_TRIE;

struct TrieNode {
    int nxt[B_TRIE];
    int isEnd;
    int cnt;
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

    void ins(int x) {
        // x is the number to add to the trie
        int cur = 0;
        for (int i = L_TRIE - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            int &nx = nodes[cur].nxt[id];
            if (nx == -1) {
                nx = addnode();
            }
            nodes[nx].cnt++;
            cur = nx;
        }
    }
    ll solve(int cur, int b) {
        if (b == -1) return 0;
        if (cur == -1) return 0;
        int lf = nodes[cur].nxt[0];
        int rg = nodes[cur].nxt[1];

        int lfsz = lf == -1 ? 0 : nodes[lf].cnt;
        int rgsz = rg == -1 ? 0 : nodes[rg].cnt;
        return solve(lf, b - 1) + solve(rg, b - 1) + b * 1ll * lfsz * 1ll * rgsz;
    }
} trie;

int n, a;
void test_case() {
    trie.init();
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        trie.ins(a);
    }
    cout << trie.solve(0, L_TRIE - 1) << endl;
}

int main() {
// #ifndef ONLINE_JUDGE
//     freopen("in.txt", "r", stdin);
// #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
