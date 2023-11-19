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
const int N = 1e6 + 5;

map<string, int> adjstring[N];
string decode[N];

ll dp[N];
set<int> adj[N];
int freq[N];
int nb_freq[N];
int nb[N];

int n;
string s;
void dfs(int u) {
    dp[u] = freq[u];
    nb[u] = nb_freq[u];
    for (auto v : adj[u]) {
        dfs(v);
        dp[u] += dp[v];
        nb[u] += nb[v];
    }
}
ll sum = 0;
ll cur_nb = 0;
ll ans = 1e18;

string cur_string = "";
void solve(int u, int d) {
    if (adj[u].size() == 0) return;
    //dbg(u, sum, cur_nb);
    ll x = sum + (dp[u] - freq[u]) + d * cur_nb;
    ans = min(ans, x);
    sum += (dp[u] - freq[u]);
    sum += (-(nb[u] - nb_freq[u]) * d);
    cur_nb += nb[u] - nb_freq[u];
    //dbg(u, cur_string, x, dp[u] - freq[u]);
    for (auto v : adj[u]) {
        sum -= dp[v];
        sum -= ((-nb[v]) * d);
        cur_nb -= nb[v];
        //cur_string += "/" + decode[v];
        solve(v, d + 1);
        // while (cur_string.back() != '/') {
        //     cur_string.pop_back();
        // }
        // cur_string.pop_back();
        sum += dp[v];
        sum += ((-nb[v]) * d);
        cur_nb += nb[v];
    }
    sum -= (-(nb[u] - nb_freq[u]) * d);
    sum -= (dp[u] - freq[u]);
    cur_nb -= nb[u] - nb_freq[u];
}

void test_case() {
    cin >> n;
    vector<int> tmp;
    int nb = 1;
    for (int i = 0; i < n; i++) {
        cin >> s;
        string cur = "";
        int st = 0;
        // dbg("new string", s);
        int tot = 0;
        s += '/';
        for (int j = 1; j < s.size(); j++) {
            if (s[j] == '/') {
                tot++;
                if (adjstring[st].count(cur) == 0) {
                    adjstring[st][cur] = nb++;
                    decode[nb - 1] = cur;
                }

                int ini_st = st;
                st = adjstring[st][cur];
                adj[ini_st].insert(st);
                freq[st]++;
                cur = "";
                // dbg(st, cur);
            } else {
                cur += s[j];
            }
        }
        nb_freq[st]++;
    }
    dfs(0);
    solve(0, 0);
    // ans += n;
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
