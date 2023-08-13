// Mtaylor
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

const int N = 1e5 + 5;
const int MOD = 1000003;

const int MAX_AHO = N;
const int ALPHA = 128;

class AhoCorasick {
   public:
    int trie[MAX_AHO][ALPHA], ndcnt, szs[MAX_AHO], F[MAX_AHO], ids[MAX_AHO],
        nxtId[MAX_AHO];
    char children[MAX_AHO][ALPHA];
    int addnode() {
        memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
        ids[ndcnt] = -1;
        szs[ndcnt] = 0;
        return ndcnt++;
    }

    void init() {
        ndcnt = 0;
        addnode();
    }
    int getNext(int f, char c) {
        while (trie[f][c] == -1) f = F[f];
        f = trie[f][c];
        return f;
    }

    void buildFail() {
        queue<int> q;
        for (int i = 0; i < ALPHA; i++) {
            int &r = trie[0][i];
            if (~r) {
                F[r] = 0;
                nxtId[r] = 0;
                q.push(r);
            } else {
                r = 0;
            }
        }

        while (q.size()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < szs[cur]; i++) {
                char c = children[cur][i];
                int f = F[cur];
                int &nxt = trie[cur][c];
                nxtId[nxt] = F[nxt] = getNext(f, c);
                q.push(nxt);
            }
        }
    }

    int insert(string &str, int id) {
        int cur;
        int i = 0;
        for (cur = 0, i = 0; i < str.size(); i++) {
            int &nxt = trie[cur][str[i]];
            if (nxt == -1) {
                nxt = addnode();
                children[cur][szs[cur]++] = str[i];
            }
            cur = nxt;
        }
        if (ids[cur] == -1) {
            ids[cur] = id;
        }
        return ids[cur];
    }
    int getNxtId(int cur) {
        if (cur == 0) return 0;
        int &nxt = nxtId[cur];
        if (ids[nxt] != -1) {
            return nxt;
        }
        return nxt = getNxtId(nxt);
    }
    bool hasSuffixString(int cur) {
        return ids[cur] != -1 || ids[getNxtId(cur)] != -1;
    }

    vector<vector<int> > match(char *str, int cnt) {
        vector<vector<int> > v(cnt);
        for (int cur = 0, i = 0; str[i]; i++) {
            cur = getNext(cur, str[i]);
            for (int j = cur; j; j = getNxtId(j)) {
                if (ids[j] != -1) {
                    v[ids[j]].pb(i);
                }
            }
        }
        return v;
    }
} aho;
int n, a, b;
string s;
int cnt[26];
int otherdigits = 5;
ll dp[22][N][2][2][2];

ll solve(int p, int c, int lo, int up, int di) {
    if (aho.hasSuffixString(c)) return 0;
    if (p >= b) return (lo && up && di);
    ll &rs = dp[p][c][lo][up][di];
    if (rs != -1) return rs;
    rs = ((p >= a) && lo && up && di);
    rs = (rs + (otherdigits * 1ll * solve(p + 1, 0, lo, up, 1)) % MOD) % MOD;
    for (int i = 0; i < 26; i++) {
        rs = (rs + solve(p + 1, aho.getNext(c, char('a' + i)), 1, up, di)) % MOD;
        rs = (rs + solve(p + 1, aho.getNext(c, char('a' + i)), lo, 1, di)) % MOD;
        if (cnt[i])
            rs =
                (rs + solve(p + 1, aho.getNext(c, char('a' + i)), lo, up, 1)) % MOD;
    }
    return rs;
}

int main() {
    memset(dp, -1, sizeof(dp));
    cin >> a >> b;
    cin >> n;
    aho.init();
    cnt['e' - 'a']++;
    cnt['o' - 'a']++;
    cnt['i' - 'a']++;
    cnt['s' - 'a']++;
    cnt['t' - 'a']++;
    for (int i = 0; i < n; i++) {
        cin >> s;
        aho.insert(s, i);
    }

    aho.buildFail();
    ll ans = solve(0, 0, 0, 0, 0);
    cout << ans << endl;

    return 0;
}
