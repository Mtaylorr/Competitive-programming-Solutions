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
const int MOD = 1e9 + 9;

const int M = 1e7 + 1;
int n, h_0, a, b, q;
bool isValid[M];
int valid[N];
bool vis[N];
int freq[N];
int dist[N];
int mnpos[N];
string t;
int target;
void test_case() {
    memset(isValid, 0, sizeof(isValid));
    cin >> n >> t >> h_0 >> a >> b >> q;
    target = stoi(t);
    int po = 1;
    for (int i = 1; i <= n; i++) {
        po *= 10;
    }
    for (int i = 0; i < po; i++) {
        valid[i] = -1;
        vis[i] = 0;
        freq[i] = 0;
        dist[i] = 1e9;
        mnpos[i] = 1e9;
    }

    int pos = 0;
    while (!isValid[h_0]) {
        pos++;
        isValid[h_0] = 1;
        int x = h_0 % po;

        if (valid[x] == -1) {
            valid[x] = pos;
        }
        h_0 = (a * 1ll * h_0 + b) % q;
    }
    valid[target] = 0;
    valid[0] = 0;
    int mn = 1e9;

    {
        set<pair<int, int> > st;

        dist[0] = 0;
        mnpos[0] = 0;
        st.insert({0, 0});
        while (!st.empty()) {
            pair<int, int> p = *st.begin();
            st.erase(st.begin());
            int u = p.se;
            if (vis[u]) continue;
            vis[u] = u;
            if (u == target) break;
            int x = u;
            int cur = 1;

            for (int i = 0; i < n; i++) {
                int p = x % 10;
                x /= 10;
                {
                    int np = (p + 1) % 10;
                    int v = u + (np - p) * cur;
                    if ((v == target) || valid[v] >= 0) {
                        int nd = max(mnpos[u], valid[v]);

                        if (mnpos[v] > nd) {
                            mnpos[v] = nd;
                            st.insert({nd, v});
                        }
                    }
                }
                {
                    int np = (p + 9) % 10;
                    int v = u + (np - p) * cur;
                    if ((v == target) || valid[v] >= 0) {
                        int nd = max(mnpos[u], valid[v]);
                        if (mnpos[v] > nd) {
                            mnpos[v] = nd;
                            st.insert({nd, v});
                        }
                    }
                }
                cur *= 10;
            }
        }
        mn = mnpos[target];
        if (vis[target] == 0) {
            cout << "-1\n";
            return;
        }
    }
   // dbg(mn);
    {
        for (int i = 0; i < po; i++) {
            vis[i] = 0;
            freq[i] = 0;
            dist[i] = 1e9;
        }
        queue<int> q;
        q.push(0);
        vis[0] = 1;
        dist[0] = 0;
        freq[0] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 1;
            // dbg(u, dist[u], freq[u]);
            if (u == target) break;
            int x = u;
            int cur = 1;

            for (int i = 0; i < n; i++) {
                int p = x % 10;
                x /= 10;
                {
                    int np = (p + 1) % 10;
                    int v = u + (np - p) * cur;
                    if ((v == target) || (valid[v] <= mn && valid[v] >= 0)) {
                        if (dist[v] > dist[u] + 1) {
                            dist[v] = dist[u] + 1;
                            freq[v] = freq[u];
                            q.push(v);
                        } else if (dist[v] == dist[u] + 1) {
                            freq[v] = (freq[v] + 0ll + freq[u]) % MOD;
                        }
                    }
                }
                {
                    int np = (p + 9) % 10;
                    int v = u + (np - p) * cur;
                    if ((v == target) || (valid[v] <= mn && valid[v] >= 0)) {
                        if (dist[v] > dist[u] + 1) {
                            dist[v] = dist[u] + 1;
                            freq[v] = freq[u];
                            q.push(v);
                        } else if (dist[v] == dist[u] + 1) {
                            freq[v] = (freq[v] + 0ll + freq[u]) % MOD;
                        }
                    }
                }
                cur *= 10;
            }
        }
        if (vis[target]) {
            cout << dist[target] << " " << freq[target] << "\n";
        } else {
            cout << "-1\n";
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
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
