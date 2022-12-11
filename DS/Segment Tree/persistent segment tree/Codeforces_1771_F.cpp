//https://codeforces.com/contest/1771/problem/F

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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }

ll H[N];

struct Node;

struct Node {
    int sz;
    ll h;
    Node *l, *r;
    Node() {
        sz = 0;
        h = 0;
        l = r = nullptr;
    }
};

void pull_up(Node *a) {
    if (a == nullptr) return;
    a->sz = a->l->sz + a->r->sz;
    a->h = a->l->h ^ a->r->h;
}

Node *build(int l, int r) {
    if (l == r) {
        Node *n = new Node();
        return n;
    }
    Node *n = new Node();
    int m = l + (r - l) / 2;
    n->l = build(l, m);
    n->r = build(m + 1, r);
    pull_up(n);
    return n;
}

Node *flip(Node *cur, int v, int l, int r) {
    if (l == r) {
        Node *n = new Node();
        if (cur->sz == 0) {
            n->sz = 1;
            n->h = H[l];
        } else {
            n->sz = 0;
            n->h = 0;
        }
        return n;
    }
    Node *n = new Node();
    int m = l + (r - l) / 2;
    if (v <= m) {
        n->l = flip(cur->l, v, l, m);
        n->r = cur->r;
    } else {
        n->r = flip(cur->r, v, m + 1, r);
        n->l = cur->l;
    }
    pull_up(n);
    return n;
}

bool same(Node *a, Node *b) { return a->h == b->h && a->sz == b->sz; }

int n, m;
int a[N];
int xs[N];
int q;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        xs[i] = a[i];
    }

    sort(xs, xs + n);
    m = unique(xs, xs + n) - xs;

    for (int i = 0; i < m; i++) {
        H[i] = myRand(1ll << 60);
    }

    vector<Node *> nodes;
    nodes.pb(build(0, m - 1));

    for (int i = 0; i < n; i++) {
        int v = lower_bound(xs, xs + m, a[i]) - xs;
        nodes.pb(flip(nodes.back(), v, 0, m - 1));
    }
    cin >> q;
    int last = 0;
    while (q--) {
        int a, b;
        cin >> a >> b;
        int l = a ^ last;
        int r = b ^ last;
        Node *nr = nodes[r];
        Node *nl = nodes[l - 1];
         if (same(nl, nr)) {
            last = 0;
        } else {
            int lf = 0;
            int rg = m - 1;

            while (lf < rg) {
                int md = lf + (rg - lf) / 2;
                if (same(nl->l, nr->l)) {
                    nl = nl->r;
                    nr = nr->r;
                    lf = md + 1;
                } else {
                    nl = nl->l;
                    nr = nr->l;
                    rg = md;
                }
            }
            last = xs[lf];
        }
        cout << last << "\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
