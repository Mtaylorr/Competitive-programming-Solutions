//https://codeforces.com/problemset/problem/788/C
//// Mtaylor
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

int a[N];
int n, k;
int vis[N];
int dist[N];
vector<int> distincts;
void test_case() {
    cin >> n >> k;
    for (int i = 0; i <= 2 * 1005; i++) {
        vis[i] = 0;
        dist[i] = 1e9;
    }
    queue<int> q;
    int offset = 1005;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        vis[n - x + offset] = 1;
        dist[n - x + offset] = 1;
        distincts.pb(n - x);
    }
    sort(all(distincts));
    distincts.resize(unique(all(distincts)) - distincts.begin());
    for (auto u : distincts) {
        q.push(u+offset);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : distincts) {
            if (vis[u + v] || u + v > 2*1005 || u + v < 0) continue;
            vis[u + v] = 1;
            dist[u + v] = dist[u] + 1;
            q.push(u+v);
        }
    }
    if(dist[offset]<1e9){
        cout << dist[offset] << endl;
    }else{
        cout << -1;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}

