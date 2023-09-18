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

struct item {
    int key, prior;
    int cnt = 0;
    item *l, *r;
    item() {}
    item(int key) : key(key), prior(myRand(1000000000)), l(NULL), r(NULL) {}
    item(int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) {}
};
typedef item* pitem;

pitem root = nullptr;

int cnt(pitem t) { return t ? t->cnt : 0; }

void upd_cnt(pitem t) {
    if (t) t->cnt = 1 + cnt(t->l) + cnt(t->r);
}

void split(pitem t, int key, pitem& l, pitem& r) {
    if (!t)
        l = r = NULL;
    else if (t->key <= key)
        split(t->r, key, t->r, r), l = t;
    else
        split(t->l, key, l, t->l), r = t;
    upd_cnt(t);
}

void mrg(pitem& t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        mrg(l->r, l->r, r), t = l;
    else
        mrg(r->l, l, r->l), t = r;
    upd_cnt(t);
}

void ins(pitem& t, int x) {
    pitem t1, t3;
    pitem t2 = new item(x);
    split(t, x, t1, t3);
    mrg(t, t1, t2);
    mrg(t, t, t3);
}

void erase(pitem& t, int x) {
    pitem t1, t2, t3;
    split(t, x - 1, t1, t2);
    split(t2, x, t2, t3);
    delete t2;
    mrg(t, t1, t3);
}

bool search(pitem& t, int x) {
    if (t == nullptr) return 0;
    if (t->key == x) return 1;
    return t->key > x ? search(t->l, x) : search(t->r, x);
}

int index(pitem& t, int x) {
    if (t == nullptr) return 0;
    if (t->key <= x) {
        return 1 + cnt(t->l) + index(t->r, x);
    }
    return index(t->l, x);
}

int getByIndex(pitem& t, int x) {
    if (t == nullptr) return -1;
    if (cnt(t->l) == x) {
        return t->key;
    }
    return cnt(t->l) > x ? getByIndex(t->l, x)
                         : getByIndex(t->r, x - cnt(t->l) - 1);
}

int n, q;
char c;
int x;
void test_case() {
    cin >> q;
    while (q--) {
        cin >> c >> x;
        switch (c) {
            case 'I':
                if (!search(root, x)) {
                    ins(root, x);
                }
                break;
            case 'D':
                if (search(root, x)) {
                    erase(root, x);
                }
                break;
            case 'K':
                if (x > cnt(root)) {
                    cout << "invalid" << endl;
                } else {
                    cout << getByIndex(root, x - 1) << endl;
                }
                break;
            case 'C':
                cout << index(root, x - 1) << endl;
                break;
        }
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
