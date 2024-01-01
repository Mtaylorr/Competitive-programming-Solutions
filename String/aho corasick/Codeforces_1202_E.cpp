//https://codeforces.com/problemset/problem/1202/E
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
const int N = 2e5 + 5;

const int ALPHA = 128;
const int MAX_AHO = N;

class AhoCorasick {
   public:
    int trie[MAX_AHO][ALPHA], ndcnt, szs[MAX_AHO], F[MAX_AHO], ids[MAX_AHO],
        nxtId[MAX_AHO];
    int dp[MAX_AHO], cnt[MAX_AHO];
    char children[MAX_AHO][ALPHA];
    int addnode() {
        memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
        ids[ndcnt] = -1;
        szs[ndcnt] = 0;
        dp[ndcnt] = -1;
        cnt[ndcnt] = 0;
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
        cnt[cur]++;
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
    int getAllSubstrings(int cur) {
        if (cur == 0) return 0;
        if (dp[cur] != -1) {
            return dp[cur];
        }
        return dp[cur] = cnt[cur] + getAllSubstrings(getNxtId(cur));
    }

    bool hasSuffixString(int cur) {
        return ids[cur] != -1 || ids[getNxtId(cur)] != -1;
    }

    vector<int> match(string str, int cnt) {
        vector<int> v(cnt);
        for (int cur = 0, i = 0; i < str.size(); i++) {
            cur = getNext(cur, str[i]);
            for (int j = cur; j; j = getNxtId(j)) {
                if (ids[j] != -1) {
                    v[ids[j]]++;
                }
            }
        }
        return v;
    }
} aho;
string t;
string s[N];
int n;
int dp[2][N];
void test_case() {
    cin >> t;
    cin >> n;
    aho.init();

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        aho.insert(s[i], i);
    }
    aho.buildFail();
    int cur = 0;
    for (int i = 0; i < t.size(); i++) {
        cur = aho.getNext(cur, t[i]);
        dp[0][i] = aho.getAllSubstrings(cur);
    }

    aho.init();

    for (int i = 0; i < n; i++) {
        reverse(all(s[i]));
        aho.insert(s[i], i);
    }
    aho.buildFail();
    cur = 0;
    for (int i = t.size() - 1; i >= 0; i--) {
        cur = aho.getNext(cur, t[i]);
        dp[1][i] = aho.getAllSubstrings(cur);
    }
    ll ans = 0;
    for (int i = 0; i < t.size() - 1; i++) {
        ans += dp[0][i] * 1ll * dp[1][i + 1];
    }
    cout << ans << endl;
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
