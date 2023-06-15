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
const int N = 1e5 + 5;

int tree[4 * N];
int n, q;
int a[N];
int k;
void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        tree[id] = a[ns];
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    tree[id] = min(tree[l], tree[r]);
}

int query(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    if (qs > ne || qe < ns) {
        return 1e9;
    }
    if (qs <= ns && qe >= ne) {
        return tree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return min(query(qs, qe, l, ns, md), query(qs, qe, r, md + 1, ne));
}

int freq[N];
map<int, queue<int> > pos;

void preprocess(int l, int r, int lstmn = 0) {
    if (l > r) return;
    int mn = query(l, r);
    int p;
    freq[r - l + 1] += mn - lstmn;
    while (!pos[mn].empty() && ((p = pos[mn].front()) <= r)) {
        pos[mn].pop();
        preprocess(l, p - 1, mn);
        l = p + 1;
    }
    preprocess(l, r, mn);
}

void test_case() {
    cin >> n >> q;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        pos[a[i]].push(i);
    }
    build();
    preprocess(0, n - 1);
    int cur = n;
    while (q--) {
        cin >> k;
        while (cur >= 1 && k) {
            int m = min(freq[cur], k);
            k -= m;
            freq[cur] -= m;
            sum -= m * 1ll * cur;
            if (freq[cur] == 0) {
                cur--;
            }
        }
        cout << sum << endl;
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
