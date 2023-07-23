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
set<vector<pair<int, int> > > vis[N];
int n;
ll x[N], y[N];
bool colinear(int i, int j, int k) {
    return (y[k] - y[i]) * (x[j] - x[i]) - (y[j] - y[i]) * (x[k] - x[i]) == 0;
}

bool solve(int p, vector<pair<int, int> > v) {
    if (p >= n) {
        return 1;
    }
    if (vis[p].count(v)) return 0;
    vis[p].insert(v);
    for (auto &u : v) {
        if (u.se != -1 && colinear(u.fi, u.se, p)) {
            return solve(p + 1, v);
        }
    }
    int s = v.size();
    for (int i = 0; i < s; i++) {
        if (v[i].se == -1) {
            v[i].se = p;
            if (solve(p + 1, v)) return 1;
            v[i].se = -1;
        }
    }
    if (v.size() < 3) {
        v.pb({p, -1});
        if (solve(p + 1, v)) return 1;
        v.pop_back();
    }
    return 0;
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    /*for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                dbg(i,j,k,colinear(i,j,k));
            }
        }
    }*/
    bool ans = solve(0, {});
    if (ans) {
        cout << "possible";
    } else {
        cout << "impossible";
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
