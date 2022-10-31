//https://codeforces.com/problemset/problem/1187/D
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

int a[N], freq[N],n,b[N];
queue<int> pos[N];

typedef int dtype;
dtype OUT_OF_RANGE = 1e9;
dtype segtree[4 * N];

dtype mrg(dtype &a,dtype & l, dtype &r){
    return a=min(l,r);
}

void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        segtree[id] = a[ns];
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    mrg(segtree[id],segtree[l],segtree[r]);
}

void upd(int p, dtype v, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns > p || ne < p)
        return;
    if (ns == ne) {
        segtree[id] = v;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(p, v, l, ns, md);
    upd(p, v, r, md + 1, ne);
    mrg(segtree[id],segtree[l],segtree[r]);
}


dtype query(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns > qe || ne < qs)
        return OUT_OF_RANGE;
    if (qs <= ns && qe >= ne) {
        return segtree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    dtype la = query(qs, qe, l, ns, md);
    dtype ra = query(qs, qe, r, md + 1, ne);
    dtype ca;
    mrg(ca, la, ra);
    return ca;
}


void solve() {
    cin >> n;
    for(int i=1;i<=n;i++){
        freq[i]=0;
        while(!pos[i].empty()){
            pos[i].pop();
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
        pos[a[i]].push(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        freq[b[i]]--;
    }
    for (int i = 1; i <= n; i++) {
        if (freq[i]) {
            cout << "NO\n";
            return;
        }
    }
    build();
    for(int i=0;i<n;i++){
        int p = pos[b[i]].front();
        pos[b[i]].pop();
        int x = query(0,p);
        if(x<b[i]){
            cout << "NO\n";
            return ;
        }
        upd(p, 1e9);
    }
    cout << "YES\n";
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
