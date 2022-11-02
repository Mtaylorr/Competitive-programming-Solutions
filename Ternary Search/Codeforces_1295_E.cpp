//https://codeforces.com/problemset/problem/1295/E
//Mtaylor 
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
void dbg_out() {cerr<<endl;}
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << ' '<<H;dbg_out(T...);}
#define dbg(...) cerr << "(" << #__VA_ARGS__<<"):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;

struct FenwickTree {
    vector<ll> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    ll mrg(ll &x, ll &y) { return x + y; }

    void upd(int x, ll v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    ll getprefix(int x) {
        if (x == 0) return 0;
        ll rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    ll getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
} ft1,ft2;

int n;
int p[N],a[N];
ll calc(int u){
    return ft1.getrange(u+1,n) + ft2.getprefix(u);
}

void solve(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> p[i];
    }
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    ll ans = min(a[0],a[n-1]);
    ft1.init(n+1);
    ft2.init(n+2);
    for(int i=n-1;i>=0;i--){
        ft2.upd(p[i],a[i]);
    }
    for(int i=0;i<n-1;i++){
        ft2.upd(p[i],-a[i]);
        ft1.upd(p[i],a[i]);
        int l=1;
        int r=n-1;
        while(r-l>=3){
            ll m1 = l+(r-l)/3;
            ll m2 = r-(r-l)/3;
            ll v1 = calc(m1);
            ll v2 = calc(m2);
            if(v1>v2){
                l=m1;
            }else{
                r=m2;
            }
        }
        for(int i=l;i<=r;i++){
            ans=min(ans, calc(i));
        }
    }
    cout << ans;

}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    //cin >>T;
    T=1;
    while(T--){
        solve();
    }
    return 0;
}
