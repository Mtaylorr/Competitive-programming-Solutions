// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
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
int n;
vector<pair<int, int> > edges;
vector<int> qu[20];
int currentQuery[N];
vector<int> adj[N];
vector<int> simualteQuery() {
    vector<int> to_ret(n, 0);
    for (int i = 0; i < n; i++) {
        for (auto &v : adj[i]) {
            if (currentQuery[v]) {
                to_ret[i]++;
            }
        }
    }
    return to_ret;
}

void query(int p, int id) {
    cout << "QUERY ";
    for (int i = 0; i < n; i++) {
        if ((i / p) % 2 == 0) {
            cout << 1;
            currentQuery[i] = 1;
        } else {
            cout << 0;
            currentQuery[i] = 0;
        }
    }
    cout << endl;
    qu[id].resize(n);
    for (int i = 0; i < n; i++) {
        cin >> qu[id][i];
    }
    //qu[id] = simualteQuery();
}
void printAnswer() {
    cout << "ANSWER\n";
    for (auto &u : edges) {
        cout << u.fi << " " << u.se << endl;
    }
    return;
}

void rem(int u, int v, int lstid) {
    for (int i = lstid; i >= 0; i--) {
        if (v < (1 << i)) {
            qu[i][u]--;
        } else {
            v -= (1 << i);
        }
    }
}

void test_case() {
    cin >> n;
    // adj[0].pb(3);
    // adj[3].pb(0);
    // adj[3].pb(1);
    // adj[1].pb(3);
    // adj[4].pb(3);
    // adj[3].pb(4);
    // adj[2].pb(4);
    // adj[4].pb(2);
    if (n == 2) {
        edges.pb({1, 2});
        printAnswer();
        return;
    }
    int lstid = 0;
    for (int i = 0; (1 << i) <= n; i++) {
        query(1 << i, i);
        lstid = i;
    }
    if ((1 << lstid) < n) {
        ++lstid;
        query(1 << lstid, lstid);
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (qu[lstid][i] == 1) {
            q.push(i);
        }
    }
    int r = n - 1;
    while (r--) {
        int u = q.front();
        q.pop();
        int nxt = 0;
        for (int i = lstid; i >= 0; i--) {
            if (!qu[i][u]) {
                nxt += (1 << i);
            }
        }
        edges.emplace_back(u + 1, nxt + 1);
        rem(nxt, u, lstid);
        if (qu[lstid][nxt] == 1) {
            q.push(nxt);
        }
    }
    printAnswer();
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen("in.txt", "r", stdin);
#endif
    int T = 1;
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
