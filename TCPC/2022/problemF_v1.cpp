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
int tree[2][4 * N];
int csum[N];
string s;
int n, q;

void build(int id = 0, int ns = 1, int ne = n) {
    if (ns == ne) {
        tree[0][id] = tree[1][id] = csum[ns];
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    tree[0][id] = max(tree[0][l], tree[0][r]);
    tree[1][id] = min(tree[1][l], tree[1][r]);
}

int querymin(int qs, int qe, int v, int id = 0, int ns = 1, int ne = n) {
    if (qs > ne || qe < ns) {
        return -1;
    }
    if (tree[1][id] + v >= 0) return -1;
    if (ns == ne) {
        return ns;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    int p = querymin(qs, qe, v, l, ns, md);
    if (p == -1) {
        p = querymin(qs, qe, v, r, md + 1, ne);
    }
    return p;
}

int querymax(int qs, int qe, int id = 0, int ns = 1, int ne = n) {
    if (qs > ne || qe < ns) {
        return 0;
    }
    if (qs <= ns && qe >= ne) {
        return tree[0][id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return max(querymax(qs, qe, l, ns, md), querymax(qs, qe, r, md + 1, ne));
}

void test_case() {
    cin >> n >> q;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        csum[i] = csum[i - 1] + (s[i - 1] == '*') - (s[i - 1] == '/');
    }
    build();
    while (q--) {
        int l, r;
        cin >> l >> r;
        int mx = 0;
        bool gotToSecondPart = false;
        int v = 0;
        if (l == 1) {
            gotToSecondPart = true;
        } else {
            int pmin = querymin(1, l - 1, v);
            if (pmin == -1) pmin = l;

            mx = max(mx, querymax(1, pmin - 1) + v);
            if (pmin >= l) {
                gotToSecondPart = true;
            } else {
                mx++;
            }
        }
        v = csum[l - 1] - csum[r];
        if (r != n) {
            int pmin = querymin(r + 1, n, v);
            if (pmin == -1) pmin = n + 1;
            mx = max(mx, querymax(r + 1, pmin - 1) + v);
            if (pmin <= n) {
                mx++;
            }
        }
        cout << mx + 1 << endl;
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
