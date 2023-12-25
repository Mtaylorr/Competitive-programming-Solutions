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
int k, w;
int t[N];
vector<int> p[N], v[N];
int f[N];
bool done[N];
bool donew[N];
vector<int> adj[N];
string st[N];
void test_case() {
    cin >> k >> w;
    for (int i = 0; i < k; i++) {
        cin >> t[i];
    }
    for (int i = 0; i < w; i++) {
        int m, _p, _v;
        cin >> st[i];
        cin >> m;

        while (m--) {
            cin >> _p >> _v;
            --_p;
            p[i].pb(_p);
            v[i].pb(_v);
            f[i] += _v != t[_p];
            if (_v != t[_p]) {
                adj[_p].pb(i);
            }
        }
    }
    vector<int> av;
    for (int i = 0; i < w; i++) {
        if (f[i] == 0) {
            av.pb(i);
        }
    }
    vector<int> ans;

    while (av.size()) {
        int x = av.back();
        av.pop_back();
        ans.pb(x);
        donew[x] = 1;
        for (int i = 0; i < v[x].size(); i++) {
            int _v = v[x][i];
            int _p = p[x][i];
            if (done[_p]) continue;
            done[_p] = 1;
            for (auto &y : adj[_p]) {
                f[y]--;
                if (f[y] == 0) {
                    av.pb(y);
                }
            }
        }
    }
    reverse(all(ans));
    for (int i = 0; i < k; i++) {
        if (!done[i] && t[i] != 0) {
            cout << "IMPOSSIBLE";
            return;
        }
    }
    for (auto &u : ans) {
        cout << st[u] << " ";
    }
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
