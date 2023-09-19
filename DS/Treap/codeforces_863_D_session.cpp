//https://codeforces.com/contest/863/problem/D
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

typedef struct item* pitem;
struct item {
    int prior, value, cnt;
    bool rev;
    pitem l, r;
    item(int value) : value(value), rev(false), cnt(0) {
        prior = myRand(1e9);
        l = r = nullptr;
    }
};
pitem root = nullptr;

int cnt(pitem it) { return it ? it->cnt : 0; }

void upd_cnt(pitem it) {
    if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push(pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap(it->l, it->r);
        if (it->l) it->l->rev ^= true;
        if (it->r) it->r->rev ^= true;
    }
}

void mrg(pitem& t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        mrg(l->r, l->r, r), t = l;
    else
        mrg(r->l, l, r->l), t = r;
    upd_cnt(t);
}

void split(pitem t, pitem& l, pitem& r, int key, int add = 0) {
    if (!t) return void(l = r = 0);
    push(t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split(t->l, l, t->l, key, add), r = t;
    else
        split(t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
    upd_cnt(t);
}

void reverseRange(pitem t, int l, int r) {
    if (l == r) return;
    pitem t1, t2, t3;
    split(t, t2, t3, r + 1);
    split(t2, t1, t2, l);
    t2->rev ^= true;
    mrg(t, t1, t2);
    mrg(t, t, t3);
}

void shiftRange(pitem t, int l, int r) {
    if (l == r) return;
    pitem t1, t2, t3, t4;
    split(t, t3, t4, r + 1);
    split(t3, t2, t3, r);
    split(t2, t1, t2, l);
    mrg(t, t1, t3);
    mrg(t, t, t2);
    mrg(t, t, t4);
}

int getByIndex(pitem& t, int pos) {
    pitem t1, t2, t3;
    split(t, t2, t3, pos + 1);
    split(t2, t1, t2, pos);
    int to_ret = t2->value;
    mrg(t, t1, t2);
    mrg(t, t, t3);
    return to_ret;
}

int n, q, m;
int a[N];
void test_case() {
    cin >> n >> q >> m;
    root = nullptr;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mrg(root, root, new item(a[i]));
    }
    while (q--) {
        int ty, l, r;
        cin >> ty >> l >> r;
        if (ty == 1) {
            shiftRange(root, --l, --r);
        } else {
            reverseRange(root, --l, --r);
        }
    }
    while (m--) {
        int p;
        cin >> p;
        cout << getByIndex(root, --p) << " ";
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
